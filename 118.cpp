/*
	Author: Andreea Musat
	Date: 16 sept 2017
	
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=54
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> point; // (x, y)

unordered_map<char, int> directions;
point upper_right;
set<point> ignore_set;

/* Addition for pairs of (int, int) */
point operator+(const point& p1, const point& p2)
{
	point result;
	result.first = p1.first + p2.first;
	result.second = p1.second + p2.second;
	return result;
}

/* Get left direction index for current direction */
inline int getLeft(int dir)
{
	return (dir + 3) % 4;
}

/* Get right direction index for current direction */
inline int getRight(int dir)
{
	return (dir + 1) % 4;
}

/* Get char direction from index */
inline int getDir(int dir)
{
	if (dir == 0) return 'N';
	if (dir == 1) return 'E';
	if (dir == 2) return 'S';
	if (dir == 3) return 'W';
}

/* Get displacement for index direction */
inline pair<int, int> getDeltaPos(int dir)
{
	if (dir == 0) return make_pair(0, 1);
	if (dir == 1) return make_pair(1, 0);
	if (dir == 2) return make_pair(0, -1);
	if (dir == 3) return make_pair(-1, 0);
}

/* check if the robot is out of bounds */
inline bool amIOutOfBounds(point p)
{
	return (p.first < 0 || 
		   p.first > upper_right.first ||
		   p.second < 0 ||
		   p.second > upper_right.second);	
}

class RobotPos
{
public:
	point position;			// current position of robot
	char orientation;		// current orientation of robot (N, S, E, W)
	bool was_lost;			// true if robot fell (was out of bounds at some point)
	string instructions;	// string of L(eft), R(ight), F(orward) the robot has to follow

	void followInstructions()
	{
		for (size_t i = 0; i < instructions.size(); i++)
		{
			if (instructions[i] == 'R')
			{
				orientation = getDir(getRight(directions[orientation]));
			}
			if (instructions[i] == 'L')
			{
				orientation = getDir(getLeft(directions[orientation]));
			}
			if (instructions[i] == 'F')
			{
				pair<int, int> deltaPos = getDeltaPos(directions[orientation]);
				
				/* If current position is a scented one and the current instruction 
					would make the robot fall, then ignore this instruction */
				if (ignore_set.find(position) != ignore_set.end() &&
					amIOutOfBounds(position + deltaPos))
				{
					continue;
				}

				/* Otherwise move robot */
				position.first += deltaPos.first;
				position.second += deltaPos.second;

				/* If robot will fall after this instruction, set the was_lost variable and 
					restore the previous position. Also, add current position to the set of 
					scented cells */
				if (amIOutOfBounds(position))
				{
					position.first -= deltaPos.first;
					position.second -= deltaPos.second;
					was_lost = true;
					ignore_set.insert(position);
					break;
				}
			}
		}
	}
};

int main()
{
	directions['N'] = 0;
	directions['E'] = 1;
	directions['S'] = 2;
	directions['W'] = 3;

	RobotPos rp;
	cin >> upper_right.first >> upper_right.second;

	while (cin >> rp.position.first >> rp.position.second >> rp.orientation)
	{
		rp.was_lost = false;
		cin >> rp.instructions;
		rp.followInstructions();
		cout << rp.position.first << " " << rp.position.second << " " << rp.orientation << (rp.was_lost ? " LOST\n" : "\n");
	}
	return 0;
}
