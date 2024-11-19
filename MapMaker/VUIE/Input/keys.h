struct
{
    bool _1, _2, _3, _4, _5, _6, _7, _8, _9, _0; //

    bool q, w, e, r, t, y, u, i, o, p, //
        a, s, d, f, g, h, j, k, l, ç,  //
        z, x, c, v, b, n, m;           //

    bool space;                 //
    bool leftShift, rightShift; //
    bool leftCtrl, rightCtrl;   //
    bool alt, altgr;            //

    bool leftArrow, rightArrow, upArrow, downArrow; //

} keys;

void keysDown(unsigned char key, int x, int y)
{
    if (key == 'w' == 1)
    {
        keys.w = true;
    }
    if (key == 's' == 1)
    {
        keys.s = true;
    }
}

void keysUp(unsigned char key, int x, int y)
{
    if (key == 'w' == 1)
    {
        keys.w = false;
    }
    if (key == 's' == 1)
    {
        keys.s = false;
    }
}

void startKeyboard()
{
    glutKeyboardFunc(keysDown);
    glutKeyboardUpFunc(keysUp);
}