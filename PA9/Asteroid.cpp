#include "Asteroid.h"

int Asteroid::pointsPerSide = 50;
RenderWindow* Asteroid::window = nullptr;
Texture* Asteroid::texture = nullptr;
float Asteroid::angularFrequencyLimit = 5;
int Asteroid::speedLimit = 2;
int Asteroid::sizeLimit = 50;
int Asteroid::sizeMin = 10;
int Asteroid::screenDimensions[2] = { WIDTH, HEIGHT };

Asteroid::~Asteroid()
{
	delete xOffsets;
	delete yOffsets;
}

Asteroid::Asteroid()
{
	generateSize();
	generateVelocity();
	generatePosition();
	generateShape();
	collidesPlayer = false;
	collidesBullet = false;
	active = true;
}

void Asteroid::generateVelocity(void)
{
	float xVelocity = 0.0;
	float yVelocity = 0.0;

	xVelocity = (getRandomIntOnRange(0, 1) ? 1 : -1) * getRandomIntOnRange(1, speedLimit);
	yVelocity = (getRandomIntOnRange(0, 1) ? 1 : -1) * getRandomIntOnRange(1, speedLimit);


	velocity = Vector2f(xVelocity, yVelocity);
}

void Asteroid::generatePosition(void)
{
	float xVelocity = 0.0;
	float yVelocity = 0.0;
	bool xBias = false;

	xBias = (bool)getRandomIntOnRange(0, 1);
	xVelocity = velocity.x;
	yVelocity = velocity.y;

	if (xBias)
	{
		if (xVelocity < 0)
		{
			position.x = screenDimensions[0] + size[1];
		}
		else
		{
			position.x = -size[3];
		}

		if (yVelocity < 0)
		{
			position.y = getRandomIntOnRange(screenDimensions[1] / 2, screenDimensions[1]);
		}
		else
		{
			position.y = getRandomIntOnRange(0, screenDimensions[1] / 2);
		}
	}
	else
	{
		if (xVelocity < 0)
		{
			position.x = getRandomIntOnRange(screenDimensions[0] / 2, screenDimensions[0]);
		}
		else
		{
			position.x = getRandomIntOnRange(0, screenDimensions[0] / 2);
		}

		if (yVelocity < 0)
		{
			position.y = screenDimensions[1] + size[0];
		}
		else
		{
			position.y = -size[2];
		}
	}
}

void Asteroid::generateSize(void)
{
	float currentSize = 0.0;
	for (int i = 0; i < 4; i++)
	{
		size[i] = getRandomIntOnRange(sizeMin, sizeLimit);
	}
}

void printArray(int* arr, int n)
{
	int integer = 0;

	//std::cout << "{ ";
	for (int i = 0; i < n - 1; i++)
	{
		integer = arr[i];
		//std::cout << integer << ", ";
	}
	//std::cout << arr[n - 1] << " }" << std::endl;
}

void Asteroid::generateShape()
{
	int xPos = 0;
	int yPos = 0;



	angularFrequency = getRandomFloatOnRange(0, angularFrequencyLimit);

	xPos = position.x;
	yPos = position.y;


	asteroidShape.setPointCount(pointsPerSide * 4);
	asteroidShape.setTexture(texture);
	asteroidShape.setTextureRect(IntRect(100, 100, 1000, 1000));
	int* currentXPointArray = nullptr;
	int* currentYPointArray = nullptr;
	int* xPointArrays[4];
	int* yPointArrays[4];
	int newExtremes[4];
	int* x = nullptr;
	int* f1x = nullptr;
	int* f2x = nullptr;
	int* f3x = nullptr;



	int counter = 0;

	newExtremes[counter] = 0 - size[counter++];
	newExtremes[counter] = 0 - size[counter++];
	newExtremes[counter] = 0 + size[counter++];
	newExtremes[counter] = 0 + size[counter++];



	counter = 0;

	xPointArrays[counter++] = getRandomSequenceOnRange(0, newExtremes[1], pointsPerSide);
	xPointArrays[counter++] = getRandomSequenceOnRange(newExtremes[1], 0, pointsPerSide);
	xPointArrays[counter++] = getRandomSequenceOnRange(0, newExtremes[3], pointsPerSide);
	xPointArrays[counter++] = getRandomSequenceOnRange(newExtremes[3], 0, pointsPerSide);

	counter = 0;

	yPointArrays[counter++] = getRandomSequenceOnRange(newExtremes[0], 0, pointsPerSide);
	yPointArrays[counter++] = getRandomSequenceOnRange(0, newExtremes[2], pointsPerSide);
	yPointArrays[counter++] = getRandomSequenceOnRange(newExtremes[2], 0, pointsPerSide);
	yPointArrays[counter++] = getRandomSequenceOnRange(0, newExtremes[0], pointsPerSide);

	//calculate center of mass

	x = new int[pointsPerSide * 2];
	f1x = new int[pointsPerSide * 2]; //f - g
	f2x = new int[pointsPerSide * 2]; //x(f - g)
	f3x = new int[pointsPerSide * 2]; //1/2(f^2 - g^2)

	xOffsets = new int[pointsPerSide * 4];
	yOffsets = new int[pointsPerSide * 4];

	int currentXPoint = 0;
	int currentYPoint = 0;



	//population x and y coordinates
	for (int i = 0; i < 4; i++)
	{
		currentXPointArray = xPointArrays[i];
		currentYPointArray = yPointArrays[i];
		for (int j = 0; j < pointsPerSide; j++)
		{
			currentXPoint = currentXPointArray[j];
			currentYPoint = currentYPointArray[j];

			xOffsets[pointsPerSide * i + j] = currentXPoint;
			yOffsets[pointsPerSide * i + j] = currentYPoint;

		}
	}

	for (int i = 0; i < pointsPerSide; i++)
	{
		x[i] = xPointArrays[1][i];
		f1x[i] = yPointArrays[1][i] - yPointArrays[0][pointsPerSide - 1 - i];
		f2x[i] = x[i] * f1x[i];
		f3x[i] = 0.5 * (pow(yPointArrays[1][i], 2) - pow(yPointArrays[0][pointsPerSide - 1 - i], 2));
	}

	for (int i = 0; i < pointsPerSide; i++)
	{
		x[pointsPerSide + i] = xPointArrays[2][i];
		f1x[pointsPerSide + i] = yPointArrays[2][i] - yPointArrays[3][pointsPerSide - 1 - i];
		f2x[pointsPerSide + i] = x[pointsPerSide + i] * f1x[pointsPerSide + i];
		f3x[pointsPerSide + i] = 0.5 * (pow(yPointArrays[2][i], 2) - pow(yPointArrays[3][pointsPerSide - 1 - i], 2));
	}

	int area = 0.0;

	area = leftRiemannSum(x, f1x, pointsPerSide * 2);
	centerOfMassX = (1 / (float)area) * (leftRiemannSum(x, f2x, pointsPerSide * 2));
	centerOfMassY = (1 / (float)area) * (leftRiemannSum(x, f3x, pointsPerSide * 2));


	for (int i = 0; i < 4; i++)
	{
		currentXPointArray = xPointArrays[i];
		currentYPointArray = yPointArrays[i];
		for (int j = 0; j < pointsPerSide; j++)
		{
			asteroidShape.setPoint(j + (i * pointsPerSide), Vector2f(currentXPointArray[j] - centerOfMassX, currentYPointArray[j] - centerOfMassY));
		}
	}

	asteroidShape.setPosition(xPos + centerOfMassX, yPos + centerOfMassY);

	delete x;
	delete f1x;
	delete f2x; 
	delete f3x;
	
	for(int i = 0; i < 4; i++)
	{
		delete xPointArrays[i];
		delete yPointArrays[i];
	}
}

bool Asteroid::isOffScreen(void)
{
	bool offScreen = true;

	int currentXOffset = 0;
	int currentYOffset = 0;
	int currentXCoordinate = 0;
	int currentYCoordinate = 0;
	int currentXPosition = 0;
	int currentYPosition = 0;

	currentXPosition = asteroidShape.getPosition().x;
	currentYPosition = asteroidShape.getPosition().y;

	//printArray(xOffsets, pointsPerSide * 4);
	
	if (centerOfMassX < 0 || centerOfMassX > WIDTH || centerOfMassY < 0 || centerOfMassY > HEIGHT) {
		for (int i = 0; i < 4 * pointsPerSide && offScreen; i++) {
			currentXOffset = xOffsets[i];
			currentYOffset = yOffsets[i];

			currentXCoordinate = currentXOffset + currentXPosition - centerOfMassX;
			currentYCoordinate = currentYOffset + currentYPosition - centerOfMassY;

			if (!(currentXCoordinate < 0 || currentXCoordinate > screenDimensions[0] || currentYCoordinate < 0 || currentYCoordinate > screenDimensions[1]))
			{
				offScreen = false;
			}
		}
	}

	return offScreen;
}

void Asteroid::move(void)
{
	asteroidShape.move(velocity);
	asteroidShape.rotate(angularFrequency);
	updateExtremes();
}

void Asteroid::drawAsteroid(void)
{
	//std::cout << "WINDOW: " << window;
	(*window).draw(asteroidShape);
}

int getRandomIntOnRange(int min, int max)
{
	int randomInt = 0;
	int range = 0;

	range = max - min;

	randomInt = (rand() % (range + 1)) + min;

	return randomInt;
}

int* getRandomSequenceOnRange(int min, int max, int n)
{
	int* randomSequence = nullptr;
	int randomInteger = 0;
	bool ascending = true;

	randomSequence = new int[n];

	randomSequence[0] = min;
	randomSequence[n - 1] = max;

	if (min > max)
	{
		ascending = false;
		int temp = 0;
		temp = min;
		min = max;
		max = temp;
	}

	for (int i = 1; i < n - 1; i++)
	{
		randomInteger = getRandomIntOnRange(min, max);
		randomSequence[i] = randomInteger;
	}

	selectionSortRecursive(randomSequence, n, ascending);

	return randomSequence;
}

void selectionSortRecursive(int* arr, int size, bool ascending)
{
	if (size > 1)
	{
		int swapIndex = 0;
		if (ascending)
		{
			swapIndex = getMinIndex(arr, size);
		}
		else
		{
			swapIndex = getMaxIndex(arr, size);
		}
		swap(arr, 0, swapIndex);
		selectionSortRecursive(&arr[1], size - 1, ascending);
	}
}

int getMinIndex(int* arr, int size)
{
	int minIndex = 0;
	int integer = 0;


	for (int i = 1; i < size; i++)
	{
		integer = arr[i];

		if (integer < arr[minIndex])
		{
			minIndex = i;
		}
	}

	return minIndex;
}

int getMaxIndex(int* arr, int size)
{
	int maxIndex = 0;
	int integer = 0;


	for (int i = 1; i < size; i++)
	{
		integer = arr[i];

		if (integer > arr[maxIndex])
		{
			maxIndex = i;
		}
	}

	return maxIndex;
}

void swap(int* arr, int i, int j)
{
	int temp = 0;

	temp = arr[i];

	arr[i] = arr[j];
	arr[j] = temp;
}

float getRandomFloatOnRange(int min, int max)
{
	float randomFloat = 0.0;
	float randomDecimal = 0.0;
	int randomInt = 0;
	int numerator = 0;
	int denominator = 0;

	randomInt = getRandomIntOnRange(min, max - 1);
	denominator = 1000000;
	numerator = getRandomIntOnRange(0, 1000000);
	randomDecimal = ((float)numerator) / denominator;
	randomFloat = randomInt + randomDecimal;

	return randomFloat;
}

float getCenter(float x1, float x2)
{
	return (x1 + x2) / 2;
}

int leftRiemannSum(int* x, int* fx, int n)
{
	int riemannSum = 0;

	int currentx = 0;
	int nextx = 0;
	int dx = 0;
	int currentfx = 0;

	for (int i = 0; i < n - 1; i++)
	{
		currentx = x[i];
		nextx = x[i + 1];
		dx = nextx - currentx;
		currentfx = fx[i];

		riemannSum += dx * currentfx;
	}

	return riemannSum;
}

