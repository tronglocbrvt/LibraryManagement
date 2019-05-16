
#if defined(_WIN32) || defined(_WIN64)
	void enable_raw_mode()
	{
	    
	}

	void disable_raw_mode()
	{
	    
	}
#else
	#include <sys/ioctl.h>
	#include <termios.h>
	#include <stdio.h>

	void enable_raw_mode()
	{
	    termios term;
	    tcgetattr(0, &term);
	    term.c_lflag &= ~(ICANON | ECHO); // Disable echo as well
	    tcsetattr(0, TCSANOW, &term);
	}

	void disable_raw_mode()
	{
	    termios term;
	    tcgetattr(0, &term);
	    term.c_lflag |= ICANON | ECHO;
	    tcsetattr(0, TCSANOW, &term);
	}

	bool kbhit()
	{

	    int byteswaiting;
	    ioctl(0, FIONREAD, &byteswaiting);
	    
	    return byteswaiting > 0;
	}


	static struct termios old;
	static struct termios news;

	/* Initialize new terminal i/o settings */
	void initTermios(int echo) 
	{
	  tcgetattr(0, &old); /* grab old terminal i/o settings */
	  news = old; /* make new settings same as old settings */
	  news.c_lflag &= ~ICANON; /* disable buffered i/o */
	  if (echo) {
	      news.c_lflag |= ECHO; /* set echo mode */
	  } else {
	      news.c_lflag &= ~ECHO; /* set no echo mode */
	  }
	  tcsetattr(0, TCSANOW, &news); /* use these new terminal i/o settings now */
	}

	/* Restore old terminal i/o settings */
	void resetTermios(void) 
	{
	  tcsetattr(0, TCSANOW, &old);
	}

	/* Read 1 character - echo defines echo mode */
	char getch_(int echo) 
	{
	  char ch;
	  initTermios(echo);
	  ch = getchar();
	  resetTermios();
	  return ch;
	}

	/* Read 1 character without echo */
	char getch(void) 
	{
	  return getch_(0);
	}

	/* Read 1 character with echo */
	char getche(void) 
	{
	  return getch_(1);
	}
#endif
// enable_raw_mode();
// if (kbhit())
// {
// 	 code 
// }
// disable_raw_mode();
// tcflush(0, TCIFLUSH); // Clear stdin to prevent characters appearing on prompt