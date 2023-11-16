
U16 Engine::find_best_move_8_4(const Board &b){
     std::ofstream outdata; 
     outdata.open("log.txt", std::ios_base::app);
     std::unordered_set<U16> moveset = b.get_legal_moves();
     Board *b1 = new Board(b); 
     
    auto moveset = b.get_legal_moves();
    if (moveset.size() == 0) {
        std::cout << "Could not get any moves from board!\n";
        std::cout << board_to_str(&b.data);
        this->best_move = 0;
    }
    else {
        if(no_start_moves_8_4!=0 && b.data.player_to_play==(1<<6)){
            this->best_move=start_moves_8_4[10-no_start_moves_8_4];
            no_start_moves_8_4--;
        }
        else if(b.data.player_to_play==(1<<7)){
            // U8 des = getp1(start_moves[6-no_start_moves]);
            // U8 src = getp0(start_moves[6-no_start_moves]);
            // U16 des_new= 0x0000;
            // des_new+=(6-getx(des));
            // des_new+=((6-gety(des))<<3);
            // U16 src_new= 0x0000;
            // src_new+=(6-getx(src));
            // src_new+=((6-gety(src))<<3);
            // this->best_move= des_new + (src_new<<8);
            // no_start_moves--;
                 auto moveset = b.get_legal_moves();
                U16 best_move = random_sampling(moveset)[0];
                this->best_move=best_move;
        }
        else{
        int depth_level=4; //4
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
    for(int depth=1;depth<=depth_level;depth++){
        double best_max = -99999;
        U16 max_move=0;
        bool complete=true;
        std::cout<<"at depth "<<depth;
        for (auto move : moveset)
        {   
            Board *copy_board = new Board(b);
            copy_board->do_move_(move);
        //    copy_board->data.player_to_play = (PlayerColor)(copy_board->data.player_to_play ^ (WHITE | BLACK));
            double score = alpha_beta_minimax(*copy_board, depth - 1, -99999, 99999, false, this,b.data.player_to_play);
          //  std::cout<<board_to_str(b.data.board_0)<<" score "<<score<<"\n";

            if (score > best_max)
            {
                best_max = score;
                max_move = move;
            }

        }
           best_score=best_max;
           best_move=max_move;

        std::cout<<" best move "<<move_to_str(best_move)<<"\n";
        this->best_move=best_move;
    }
   this->best_move = best_move;
        }
    }
    return best_move;
}