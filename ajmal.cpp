
U16 Engine::find_best_move_7_3(const Board &b){
     std::ofstream outdata; 
    outdata.open("log.txt", std::ios_base::app);
     std::unordered_set<U16> moveset = b.get_legal_moves();
     Board *b1 = new Board(b);
     if (moveset.size() == 0) {
        std::cout << "Could not get any moves from board!\n";
        std::cout << board_to_str(&b.data);
        this->best_move = 0;
    }
    bool is_legal_move=false;

    std::cout<<"1"<<std::endl;
    //outdata<<"1";
     if(this->no_start_moves_7_3!=0){
        if(b1->data.player_to_play==BLACK){
            U16 anti_move= get_anti_move(*b1,this->start_moves_7_3[7-this->no_start_moves_7_3]);
            outdata<<"Anti move"<< move_to_str(anti_move)<<std::endl;
            is_legal_move=moveset.count(anti_move)>0?true:false;
            b1->do_move_without_flip_(get_anti_move(*b1,this->start_moves_7_3[7-this->no_start_moves_7_3])); //correct this
        }
        else{
            is_legal_move=moveset.count(this->start_moves_7_3[7-this->no_start_moves_7_3])>0?true:false;
            b1->do_move_without_flip_(this->start_moves_7_3[7-this->no_start_moves_7_3]); 
        }
     }
     if(this->no_start_moves_7_3!=0 && b.data.player_to_play==WHITE && no_immidiate_threat(b) && no_immidiate_threat(*b1) && is_legal_move){
            this->best_move=this->start_moves_7_3[7-this->no_start_moves_7_3];
            this->no_start_moves_7_3--;
            return this->best_move;
        }
     else if(this->no_start_moves_7_3!=0 && b.data.player_to_play==BLACK && no_immidiate_threat(b) && no_immidiate_threat(*b1) && is_legal_move){
            this->best_move= get_anti_move(b,this->start_moves_7_3[7-this->no_start_moves_7_3]);
            this->no_start_moves_7_3--;
            this->best_move;
     }
    else {
        std::cout<<"2"<<std::endl;
        int depth_level=3; //4
        //if(!no_immidiate_threat(b)){
          //  depth_level=2;
        //}
     boardCounts[uniq_hash(board_to_str(&b.data))]++;

     auto moveset = b.get_legal_moves();
     std::cout <<"Legal Moves :";
     for (auto m : moveset) {
            std::cout << move_to_str(m) << " ";
        }
    std::cout <<"\n";
    double best_score = -99999;
    U16 best_move = random_sampling(moveset)[0];
    this->best_move=best_move;
    std::cout<<"random_move "<<move_to_str(this->best_move)<<"\n";
    //Board* copy_board = b.copy();
    for(int depth=depth_level;depth<=depth_level;depth++){
        double best_max = -99999;
        U16 max_move=0;
        bool complete=true;
        std::cout<<"at depth "<<depth;
        for (auto move : moveset)
        {   
            Board *copy_board = new Board(b);
            copy_board->do_move_(move);
          //  copy_board->data.player_to_play = (PlayerColor)(copy_board->data.player_to_play ^ (WHITE | BLACK));
            double score = alpha_beta_minimax(*copy_board, depth - 1, -99999, 99999, false, this,b.data.player_to_play);
          //  std::cout<<board_to_str(&b.data)<<" score "<<score<<"\n";
            outdata<<board_to_str(&b.data)<<" score "<<score<<" "<<depth<<" "<<move_to_str(move)<<"\n";

            if (score > best_max)
            {
                best_max = score;
                max_move = move;
            }

        }
           best_score=best_max;
           best_move=max_move;

        std::cout<<" best move "<<move_to_str(best_move)<<"\n";
      //  outdata<<" best move "<<move_to_str(best_move)<<"\n";
        this->best_move=best_move;
    }
   this->best_move = best_move;
        }
    return best_move;
}
