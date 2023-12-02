#include <vector>

class MazeGraph{

    public:
        MazeGraph();
        ~MazeGraph();

        void ReadTextToGraph();
        void PrintGraph();
        void RenderMaze(bool);
        void RenderCells(int a, int b, bool);
        void MazeClear();

        static std::vector<std::vector<char>> graph; //2D vector storing all elements of the text file.
        static std::vector<std::vector<short>> food; //2D vector storing small food locations from the text file.
        static unsigned x_o, y_o;
        static unsigned cellSize;
        static unsigned width, length;
        static int food_count;

    private:
        int maze_complete_fps = 0;

};