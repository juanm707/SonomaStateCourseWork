// File: CLife.h
// Author: Juan Martinez
// Project: CS215 Project 3 Spring 2017
// Description of file contents: Header file for a game of a modified version of cell life.

#ifndef CLife_H
#define CLife_H

#include <afxwin.h>
#include <string>
#include <map>
using namespace std;

#define DEF_ROWS 30
#define DEF_COLS 34

enum square_types { BORDER, EMPTY, ADDINGA, ADDINGB, PERSON, HUMAN, DELETING, RAYGUN, MAXTYPES };
enum status_types { NEW, READY, PLAYING, PAUSED, FINISHED };

class CLife
{
	public:
/*1*/		CLife ();
/*2*/		CLife (const CLife & other);
/*3*/		~CLife ();
/*4*/		CLife & operator = (const CLife & other);
/*5*/		void LoadResources ();
/*6*/		void Init (int R, int C, CFrameWnd * windowP);
/*7*/		void Instructions (CFrameWnd * windowP);
/*8*/		void Display (CFrameWnd * windowP);
/*9*/		void Click (int x, int y, CFrameWnd * windowP);
/*10*/		void Move (char direction, CFrameWnd * windowP);
/*11*/		void UpdateTime (CFrameWnd * windowP);		
/*12*/		void Message (CFrameWnd * windowP);
/*13*/		bool Done (CFrameWnd * windowP);

	private:
		struct CLifeSquare
		{
/*14*/			CLifeSquare ();
/*15*/			void Display (CDC * deviceContextP);
/*16*/			int Reset(CFrameWnd * windowP);
				square_types what;
				CRect where;
		};
/*17*/		void SetUp (CRect window);
/*18*/		void DisplayGameRect (CDC * deviceContextP);
/*19*/		void DisplayDataRect (CDC * deviceContextP);
/*20*/		void DisplayButtonRect (CDC * deviceContextP);
/*21*/		void InitRandom(CFrameWnd * windowP);
/*22*/		void Next(CFrameWnd * windowP);
/*23*/		bool Add(int row, int col, square_types what, CFrameWnd * windowP);
/*24*/		bool Delete(int row, int col, CFrameWnd * windowP);
/*25*/		void Evaluate(int row, int col, CFrameWnd * windowP);
/*26*/		string MakeString() const;

		CLifeSquare ** grid;
		int seed;
		int numRows;
		int numCols;
		int ZpopulationSize;
		int HpopulationSize;
		int generations;
		map <string, int> generationsMap;
		bool evaluating;
		status_types CLifeStatus;
		int finished;

		CRect gameRect;
		CRect dataRect;
		CRect buttonRect;
		CRect newRect;
		CRect playRect;
		CRect restartRect;
};

#endif
