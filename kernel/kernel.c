void kernel_main()
{
    char* video = (char*)0xB8000;

    video[0] = 'G';
    video[1] = 0x0F;

    video[2] = 'l';
    video[3] = 0x0F;

    video[4] = 'a';
    video[5] = 0x0F;

    video[6] = 's';
    video[7] = 0x0F;

    video[8] = 's';
    video[9] = 0x0F;

    video[10] = 'O';
    video[11] = 0x0F;

    video[12] = 'S';
    video[13] = 0x0F;

    while (1);
}