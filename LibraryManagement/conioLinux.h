#pragma once

#if defined(_WIN32) || defined(_WIN64)
	void enable_raw_mode();

	void disable_raw_mode();
#else
	#include <sys/ioctl.h>
	#include <termios.h>
	#include <stdio.h>

	void enable_raw_mode();

	void disable_raw_mode();

	bool kbhit();


	static struct termios old;
	static struct termios news;

	/* Initialize new terminal i/o settings */
	void initTermios(int echo);

	/* Restore old terminal i/o settings */
	void resetTermios(void);

	/* Read 1 character - echo defines echo mode */
	char getch_(int echo);

	/* Read 1 character without echo */
	char getch(void);

	/* Read 1 character with echo */
	char getche(void);
#endif
// enable_raw_mode();
// if (kbhit())
// {
// 	 code 
// }
// disable_raw_mode();
// tcflush(0, TCIFLUSH); // Clear stdin to prevent characters appearing on prompt