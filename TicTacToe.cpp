#include <iostream>
#include <raylib.h>
using namespace std;
const int cellsize = 250;
const int cellcount = 3;


class Player{
    private:
        int idPemain;
        string namaPemain;
        char simbolPemain;
    public:
    Player(int id){
        idPemain = id;
    }

    int getIdPemain(){
        return idPemain;
    }  
};

class Papan{
    public:
    Texture2D textureX;
    Texture2D textureO;
    int board[3][3] = {0};
    int sisaturn = 0;

     void loadTexture(){
    textureX = LoadTexture("X.png");
    textureO = LoadTexture("O.png");
        }

    void gambarboard(){
    for(int i = 0 ; i < 3; i++){
        for(int j = 0; j < 3; j++){
            DrawLine(i*cellsize, 0, i * cellsize,  cellcount * cellsize, BLACK); // vertical x awal, y awal, x akhir, y akhir
            DrawLine(0,i * cellsize, cellsize * cellcount, i * cellsize, BLACK); // horizontal x awal, y awal,x akhir, y akhir
            }
        }
    }

    void DrawTextureCenter(Texture2D texture, int x, int y){
         DrawTexture(
            texture,
            x - texture.width / 2,
            y - texture.height / 2,
            WHITE
        );
    }

    bool boardFull(int board[3][3]){
     for(int i=0;i<3;i++)
        {
        for(int j=0;j<3;j++)
            {
            if(board[i][j] == 0)
                return false;
            }
        }
    return true;
    }


    void gambarSimbol(int board[3][3]){
        for(int i = 0; i < 3; i++){
            for(int j =0; j < 3; j++){
                int X = j * cellsize + cellsize / 2; // center gambar dari index dengan rumus nilai awal * besar cell, nilai cell selanjutnya
                int Y = i * cellsize + cellsize / 2; // di tambah lalu di bagi 2, misal i = 0, maka 0 * 250 + 250 / 2 = 250 / 2 = 125;
                if(board[i][j] == 1){
                    DrawTextureCenter(textureX, X, Y);
                }else if(board[i][j] == 2){
                    DrawTextureCenter(textureO, X, Y);
                }
            }
        }
    }

    bool move(int board[3][3], int id){
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            int centerX, centerY;
            Vector2 mousePos = GetMousePosition();
            centerX= mousePos.x / cellsize; // center mouse biar dapat nilai board mana yang di pencet
            centerY= mousePos.y / cellsize; 
            cout << "mouse: " << mousePos.x << ", " << mousePos.y << endl;
            cout << "cell : " << centerX << ", " << centerY << endl;

            if(centerX >= 0 && centerX < cellcount && 
                centerY >= 0 && centerY < cellcount){ // cek apakah center nya lewat batas atau ngak.
                if(board[centerY][centerX] == 0){ // center Y karena layar menyimpan Y kartesius ke bawah dan memori baris itu ke
                        board[centerY][centerX] = id; // jadiin idpemain
                        return true;
                }
            }
        }
            return false;
    }


};


bool cekWinPlayer(int board[3][3], int id)
    {
        for(int i=0;i<3;i++)
        {
            if(board[0][i] == id &&
            board[1][i] == id &&
            board[2][i] == id)
                return true;

            if(board[i][0] == id &&
            board[i][1] == id &&
            board[i][2] == id)
                return true;
        }
        if(board[0][0] == id &&
        board[1][1] == id &&
        board[2][2] == id)
            return true;

        if(board[0][2] == id &&
        board[1][1] == id &&
        board[2][0] == id)
            return true;

        return false;
    }

class Ai{
    private:
        int AIid;
    public:
    Ai(int id = 2){
        AIid = id;
    }
    int getAIid(){
        return AIid;
    }


    int MinimaxEngine(int board[3][3], bool maximizing, Papan &papan){
        int bestscore = - 99999; // bikin dasar nilia untuk maximize nilia ai nanti.
        if(cekWinPlayer(board,1)){return -10;} // jika player menang ambil nilai minus
        else if(cekWinPlayer(board,2)){return 10;} // jika ai yang menang maka ambil nilai plus
        else if(papan.boardFull(board)){return 0;} // jika seri maka ambil nilai 0;

        if(maximizing){ //  mencari jalan terbaik ai
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(board[i][j] == 0){
                    board[i][j] = AIid;
                    int score = MinimaxEngine(board,false, papan); // setelah ai jalan di atas, giliran player, ini untuk nge cek hasil move player
                    board[i][j] = 0;
                    bestscore = max(score,bestscore);
                    }
                }
            }
            return bestscore; // balikin nilai yang di atas.
        }else{ // bagian mencari jalan terbaik player
            bestscore = 99999;
            for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(board[i][j] == 0){
                    board[i][j] = 1;
                    int score = MinimaxEngine(board,true, papan); // setelah player jalan di atas, giliran ai, ini untuk nge cek hasil move ai
                    board[i][j] = 0;
                    bestscore = min(score,bestscore);
                    }
                }
            }
        }
        return bestscore;
    }  

    void AiMove(int board[3][3], Papan &papan){
        int bestscore = -9999; 
        int ibaru = -1, jbaru = -1; // agar bisa di pasang nilai nilai yang paling bagus nanti

        for(int i = 0; i< 3; i++){
            for(int j = 0; j< 3; j++){
                if(board[i][j] == 0){
                    board[i][j] = AIid;
                    int score = MinimaxEngine(board,false, papan);
                    board[i][j] = 0;
                    if(score > bestscore){
                        bestscore = score;
                        ibaru = i;
                        jbaru = j;
                    }
                }
            }
        }
        board[ibaru][jbaru] = AIid;
    } 
};






enum GameState{
    MENU,
    PLAYING,
    GAMEOVER
};

enum Mode{
    VS_AI,
    VS_PLAYER
};


int main(){

    InitWindow(750,750,"TicTacToe AI");
    SetTargetFPS(60);
    InitAudioDevice(); //  biar ada suara nya game nya
    GameState state = MENU;
    Mode mode;
    int board[3][3]={0};
    int turn = 1;

    Papan papangame;
    papangame.loadTexture();
    Sound Suaraklik = LoadSound("Place.mp3");
    Sound SuaraGameOver = LoadSound("GameOver.mp3");

    Player Player1(1);
    Player player2(2);
    Ai bot(2);



    while(!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(Color{25,25,40,255});

        if(state == MENU)
        {
            DrawText("TIC TAC TOE",210,100,45,GOLD);
            DrawRectangle(
                200,250,
                350,80,
                BLUE
            );
            DrawText(
                "VS AI",
                330,275,
                30,
                WHITE
            );
            DrawRectangle(
                200,380,
                350,80,
                GREEN
            );
            DrawText(
                "2 PLAYER",
                290,405,
                30,
                WHITE
            );
            Vector2 mouse = GetMousePosition();
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {

                if(CheckCollisionPointRec(mouse,{200,250,350,80})){
                    PlaySound(Suaraklik);
                    mode = VS_AI;
                    state = PLAYING;
                    for(int i=0;i<3;i++)
                        for(int j=0;j<3;j++)
                            board[i][j]=0;


                    papangame.sisaturn=0;
                    turn=1;
                }
                if(CheckCollisionPointRec(
                    mouse,
                    {200,380,350,80}))
                {
                    PlaySound(Suaraklik);
                    mode = VS_PLAYER;
                    state = PLAYING;

                    for(int i=0;i<3;i++)
                        for(int j=0;j<3;j++)
                            board[i][j]=0;

                    papangame.sisaturn=0;
                    turn=1;
                }

            }

        }else if(state == PLAYING)
            {
            papangame.gambarboard();
            if(turn==1)
            {
                DrawText( "PLAYER 1 TURN", 270,40, 25, WHITE );
                if(papangame.move(board, 1)){
                    PlaySound(Suaraklik);
                    papangame.sisaturn++;
                    turn=2;
                }

            }else{
                if(mode == VS_AI){
                    DrawText( "AI Thinking...", 270,40, 25, WHITE );
                    bot.AiMove(board, papangame);
                    PlaySound(Suaraklik);
                    papangame.sisaturn++;
                    turn = 1;
                    }

                else if(mode == VS_PLAYER){
                    DrawText( "PLAYER 2 TURN", 270,40, 25, WHITE );
                    if(papangame.move(board, 2)){
                        PlaySound(Suaraklik);
                        papangame.sisaturn++;
                        turn = 1;
                        }
                    }
                }

            papangame.gambarSimbol(board);
            if(cekWinPlayer(board,1))
            {
                state=GAMEOVER;
                PlaySound(SuaraGameOver);
            }if(cekWinPlayer(board,2))
            {
                state=GAMEOVER;
                PlaySound(SuaraGameOver);
            }if(papangame.boardFull(board))
            {
                state=GAMEOVER;
                PlaySound(SuaraGameOver);
            }

         }else if(state == GAMEOVER){
            DrawText("GAME OVER", 250,150, 45,RED);
            if(cekWinPlayer(board,1) && mode == VS_AI ){
                DrawText("PLAYER WIN!",280,250,30,GREEN);
            }else if(cekWinPlayer(board,1) && mode == VS_PLAYER){
                 DrawText("PLAYER 1 WIN!",280,250,30,GREEN);
            }else if(cekWinPlayer(board,2) && mode == VS_AI){
                DrawText("AI WIN!",300,250,30,BLUE);
            }else if(cekWinPlayer(board,2) && mode == VS_PLAYER){
                 DrawText("PLAYER 2 WIN!",300,250,30,BLUE);
            }else{
                DrawText( "DRAW!",320,250,30,YELLOW);
                }

            DrawRectangle(
                220,400,
                300,70,
                DARKBLUE
            );
            DrawText(
                "MENU",
                330,420,
                30,
                WHITE
            );
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {

                Vector2 mouse=GetMousePosition();

                if(CheckCollisionPointRec(
                    mouse,
                    {220,400,300,70}))
                {
                    state=MENU;
                }

            }

        }
        EndDrawing();
    }
    UnloadTexture(papangame.textureX);
    UnloadTexture(papangame.textureO);
    UnloadSound(Suaraklik);
    UnloadSound(SuaraGameOver);
    CloseAudioDevice();
    CloseWindow();
}