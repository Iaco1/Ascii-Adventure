class Title{
    protected:
    int NWx, NWy; //North-West corner coordinates for the area the titleString covers
    int width, height;
    const char *titleString[5];

    public:
    Title();
    Title(int windowCenterX, int windowCenterY);
    int getNWx();
    int getNWy();
    int getHeight();
    int getWidth();
    const char* getTitleString(int i);
};