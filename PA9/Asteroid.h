#include "sfml.h"

class Asteroid
{
	private:
		//Vector2f size;
		Vector2f position;
		Vector2f velocity;
		ConvexShape asteroidShape;
		float angularFrequency; 
		int size[4];
		int centerOfMassX;
		int centerOfMassY;
		int* xOffsets;
		int* yOffsets;
	
	public:
		static int pointsPerSide;
		static RenderWindow* window;
		static Texture* texture;
		static float angularFrequencyLimit;
		static int speedLimit;
		static int sizeLimit; 
		static int screenDimensions[2];

		Asteroid();


		void generateShape(void);
		void setXPosition(float);
		void setYPosition(float);
		void setXVelocity(float);
		void setYVelocity(float);
		void setVelocity(Vector2f);
		void setPosition(Vector2f);
		void move(void);
		void updatePosition(void);
		void drawAsteroid(void);
		void generateVelocity(void);
		void generatePosition(void);
		void generateSize(void);
		bool collide(Vector2f);
		bool isOffScreen(void);

};

int getRandomIntOnRange(int, int);
int* getRandomSequenceOnRange(int, int, int);
void selectionSortRecursive(int*, int, bool);
int getMinIndex(int*, int);
int getMaxIndex(int*, int);
void swap(int*, int, int);
float getRandomFloatOnRange(int, int);
float getCenter(float, float);
int leftRiemannSum(int*, int*, int);
void printArray(int*, int);
