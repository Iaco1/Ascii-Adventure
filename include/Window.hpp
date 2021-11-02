class Window{
    protected:
    int width;
    int height;
    int centerX; //used to center all elements on the window
    int centerY;

    public:
    Window();
    Window(int w, int h);
    int getCenterX();
    int getCenterY();
    int getWidth();
    int getHeight();

};