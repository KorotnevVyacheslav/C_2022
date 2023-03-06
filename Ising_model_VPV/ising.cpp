//g++ ising.cpp -o mod -lglut -lGL -lGLU

#ifdef __APPLE__CC__
#include <GLUT/glut.h>
#endif

#ifdef __MSC_VER__
#include <GLUT/glut.h>
#endif

#ifdef __GNUC__
#include <GL/glut.h>
#endif

//todo: run on Apple and Microsoft devices

#include <iostream>
#include <fstream>
#include <random>
#include <string>

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;


class Physics {
  //class for physics logic functions
private:
  double * w = new double [5]; //array for probabilities

public:
  virtual void calcW(double H, double T){
    //Gibbs distribution calculation
  	double e4 = exp(-4 / T + H / T);
    double e8 = e4 * e4;
  	w[0] = w[4] = e8;
  	w[1] = w[3] = e4;
  	w[2] = exp(- abs(H) / T);
  }

  Physics(){}

  virtual ~Physics (){
    delete [] w;
  };

  Physics(const Physics& src) = delete;
  Physics(Physics && src) = delete;
  Physics& operator = (const Physics& src) = delete;

  bool metropolis(i32 value, double H, i32 sum){
    //condition for metropolis algorithm
    return sum * value + value * H <= 0
    || (rand() / (double)RAND_MAX) < w[(sum) / 2 + 2];
  }
};

struct DataContainer {
  double T, H; // variables for temperature and magnetic field
  i32 M, E, size; // variables for polarisation, system energy and lattice size
  DataContainer (double _t, double _h, i32 _m, i32 _e, i32 _size) :
  T(_t), H(_h), M(_m), E(_e), size(_size){}

  ~ DataContainer() = default;
  DataContainer(const DataContainer& src) = delete;
  DataContainer(DataContainer && src) = delete;
  DataContainer& operator = (const DataContainer& src) = delete;

  void set_values(double _t, double _h, i32 _m, i32 _e){
    // setting values
    M = _m;
    H = _h;
    E = _e;
    T = _t;
  }
};

class Table final {
  //Class for operating with spins
private:
  const i32 SIZE = 512; //number of spins in line
  const i32 SIZE_PX = 800; // number of pixels
  const i32 T_MAX = 4; // upper limit of temperature
  const i32 H_MAX = 1; // limit od module of magnetic field
  const double dT = (1.0 * T_MAX) / 100; // step of temperature changing
  const double dH = (2.0 * H_MAX) / 100;  // step of magnetic field changing

  double T = 2; // temperature
  double H = 0; // magnetic field
  i32 M; // difference between numbers of up and down spins (polarisation)
  i32 E; // total energy

  i32 ratio = 0; //variables for statistics, have not made yet
  size_t nmcs = 0;
  double ecum = 0;
  double e2cum = 0;
  double mcum = 0;
  double m2cum = 0;
  //todo: make some statistics

  Physics physics_module; // class with metropolis logical function

  i32** lattice; // 2-dimensional array for spins configuration
  //todo: replace 2-dimensional i32 array with one-dimensional bool array

  DataContainer * values = new DataContainer(T, H, M, E, SIZE);

public:

  Table (i32 _size, i32 _size_px) : SIZE(_size), SIZE_PX(_size_px){
    /*
    i32 : _size : SIZE - number of spins in line
    i32 : _size_px : SIZE _PX- number of pixels in line

    A 2-dimensional array is created in heap instead of big one for
    simplifying programmer's work
    */
    lattice = new i32*[_size]; // araay od arrays
    for(size_t i = 0; i < _size; i++) {
      lattice[i] = new i32[_size]; //array of i32
    }
  };

  virtual ~Table (){
    /*
    Deleting a 2-dimensional array
    */
    for(size_t i = 0; i < SIZE; i++) {
      delete [] lattice[i];
    }
    delete [] lattice;
    delete values;
  };

  Table(const Table& src) = delete;
  Table(Table && src) = delete;
  Table& operator = (const Table& src) = delete;

  void keyboard(unsigned char key, i32 x, i32 y){
    //Function for operating with keyboard inputs
    switch (key)
    {
    case 'w': case 'W':
    {
      T += dT; //increasing temperature
      T = (T >= T_MAX) ? T_MAX : T;
      physics_module.calcW(H, T);
      break;
    }
    case 's': case 'S':
    {
      T -= dT; //decreasing temperature
      T = (T <= 0.01) ? 0.01 : T;
      physics_module.calcW(H, T);
      break;
    }
    case 'd': case 'D':
    {
      H += dH;// increasing magnetic field
      H = (H >= H_MAX) ? H_MAX * 1.0 : H;
      physics_module.calcW(H, T);
      break;
    }
    case 'a': case 'A':
    {
      H -= dH; // decreasing magnetic field
      H = (H <= -H_MAX) ? -H_MAX * 1.0 : H;
      physics_module.calcW(H, T);
      break;
    }
    }
  }

  void motion(i32 x, i32 y){
    //function for faster operating with by-mouse temperature changing
    double k = 1 - y / (double)SIZE_PX; // coefficient of increasement
    //todo: troubles with window rescaling

    T = T_MAX * k;
    T = (T >= T_MAX) ? T_MAX : T;
    T = (T <= 0.01) ? 0.01 : T;

    physics_module.calcW(H, T); // physics module probability calculating
  }

  void display_initialization(){
    //proccess of window initialization

    setlocale(LC_ALL, "ru"); //russian language (I'm not sure it is used somewhere)
    if (!glutDeviceGet(GLUT_HAS_KEYBOARD)){
      //Checking whether user has a keyboard
      std::cout << "Your computer has not a keyboard! \n";
      throw 1;
    }
    if (!glutDeviceGet(GLUT_HAS_MOUSE)){
      //Checking whether user has a mouse
      std::cout << "Your computer has not a mouse! \n";
      throw 2;
    }

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(SIZE_PX + 100, SIZE_PX);
  	glutCreateWindow("Ising model | Metropolis"); // window label
  	glMatrixMode(GL_PROJECTION); // 2d mode
  	glLoadIdentity();
  	gluOrtho2D(0, SIZE + SIZE / 8, 0, SIZE);
  }

  void lattice_initialization(){
    //initialization of lattice
    //Main idea: setting all the spins in random direction

    M = E = 0; //setting zero

  	static std::default_random_engine generator; //random i32
  	std::uniform_int_distribution<i32> distribution(0, RAND_MAX); //array wit uniform distribution
  	for (size_t i = 0; i < SIZE; i++)
  		for (size_t j = 0; j < SIZE; j++)
  		{
        //simple ligic function for reversing
  			lattice[i][j] = ((distribution(generator) / (double)RAND_MAX >= 0.5) - 1) * 2 + 1;
  			M += lattice[i][j]; //reversing
  		}

  	for (size_t i = 0; i < SIZE; i++)
  		for (size_t j = 0; j < SIZE; j++)
  		{
        //calculating the total energy of system caused by spins interaction
  			E += (i + 1 != SIZE) ? lattice[i][j] * lattice[i + 1][j] : 0;
  			E += (j + 1 != SIZE) ? lattice[i][j] * lattice[i][j + 1] : 0;
  		}

  		for (size_t i = 0; i < SIZE; i++)
  			for (size_t j = 0; j < SIZE; j++)
  			{
          //calculating the total energy of system caused by magnetic field
  				E += lattice[i][j] * H;
  			}

  	physics_module.calcW(H, T);// physics module probability calculating
  }

  void display(){
    //function for drawing all the picture

  	glClear(GL_COLOR_BUFFER_BIT);

  	glBegin(GL_QUADS);
  	for (size_t i = 0; i < SIZE; i++)
  		for (size_t j = 0; j < SIZE; j++)
  		{
        //drawing every spin
  			glColor3f(lattice[i][j], lattice[i][j], lattice[i][j]);
  			glVertex2d(i, j + SIZE / 8);
  			glVertex2d(i, j + 1 + SIZE / 8);
  			glVertex2d(i + 1, j + 1 + SIZE / 8);
  			glVertex2d(i + 1, j + SIZE / 8);
  		}
  	glEnd();


  	glBegin(GL_QUADS);
  	{
      //drawing a temperature bar
  		glColor3f(1, 0, 0);
  		glVertex2d(SIZE, 0);
  		glVertex2d(SIZE, SIZE * T / T_MAX);
  		glVertex2d(SIZE + SIZE / 8, SIZE * T / T_MAX);
  		glVertex2d(SIZE + SIZE / 8, 0);

  		glColor3f(1, 1, 1);
  	}

  	glEnd();

  	glBegin(GL_QUADS);
  	{
      //drawing magnetic field bar
  		glColor3f(0, 1, 0);
  		glVertex2d(SIZE / 2, 0);
  		glVertex2d(SIZE / 2,  SIZE / 8);
  		glVertex2d(SIZE * (1 + H / H_MAX) / 2,  SIZE / 8);
  		glVertex2d(SIZE * (1 + H / H_MAX) / 2, 0);

  		glColor3f(1, 1, 1);
  	}

  	glEnd();
  	glutSwapBuffers();
  	glFlush();
  }

  void spin_reversing(){
    //spin reversing function
    i32 x, y, sum;//coordinates and summary of interaction energy
  	for (size_t i = 0; i < SIZE * SIZE; i++)
  	{
      //random coordinate
  		x = rand() % SIZE;
  		y = rand() % SIZE;
      //interaction energy
  		sum = lattice[(x - 1 + SIZE) % SIZE][y] +
  			lattice[(x + 1 + SIZE) % SIZE][y] +
  			lattice[x][(y - 1 + SIZE) % SIZE] +
  			lattice[x][(y + 1 + SIZE) % SIZE];

  		if (physics_module.metropolis(lattice[x][y], H, sum)) //condition for reversing
  		{
  			lattice[x][y] = -lattice[x][y];
  			ratio++;
  			M += 2 * lattice[x][y];
  			E -= 2 * lattice[x][y] * sum + 2 * lattice[x][y] * H;
  		}
  	}
  }

  DataContainer * get_values(){
    //function for extracting values for databank
    values->set_values(T, H, M, E);
    return values;
  }
};

class Saver {
private:
  i64 * counters; //array for each timer counter

  std::string * names; // array of string names of paths to file

public:
  i32 * timers; //array with timers given outside

  i64 steps; // counter for programm iterations

  const i32 num; // number of files to outstream

  Saver (i32 _num) : num(_num){
    //todo: rewrite it with unique pointer
    //whether the stream can break down during initialization
    timers = new int [_num];
    names = new std::string [_num];
    counters = new i64 [_num];

    timers[0] = 1;
    //todo callibrate

    std::string path; //path to file

    for (size_t i = 0; i < _num; i++) {

      if(i < _num - 1) timers[i + 1] = timers[i] * 10;
      path = "data/data_";
      path.append(std::to_string(timers[i]));
      path.append(".txt");

      names[i] = path;
      counters[i] = 0;

      std::ofstream file(names[i], std::ios::out);
      if (!file.is_open()) throw 3;
      //todo: working error operating for this case

      if (file.is_open()) {
        // writing data
        file << "Databank for timer " << timers[i] << "\n"
        << "n T H M E\n";
        file.close();
      }
    }
  };

  virtual ~Saver (){
    delete [] timers;
    delete [] counters;
    delete [] names;
  };

  Saver(const Saver& src) = delete;
  Saver(Saver && src) = delete;
  Saver& operator = (const Saver& src) = delete;

  i64 NOD(i64 a, i64 b){

    i64 r;
    while ((a % b) > 0)  {
      r = a % b;
      a = b;
      b = r;
    }
    std::cerr << b << " ";
    return b;
  }

  i64 NOK(i64 a, i64 b){
    return a * (b / NOK(a, b));
  }

  void save_iter(i32 iter, Table * table){
    //getting data from Table
    DataContainer * data;
    data = table -> get_values();

    counters[iter]++;

    //opening file for writing in app mode
    std::ofstream file(names[iter], std::ios::app);

    if (file.is_open()) {
      file << counters[iter] * timers[iter] << " " << data -> T
      << " " << data -> H << " "
      << (1.0 * data -> M) / (data -> size) / (data -> size)
      << " " << data -> E << "\n";
      file.close();
    }
  }

  void save(Table * table){
    //saving data for each stream
    for (size_t i = 0; i < num; i++) {
      if (steps % timers[i] == 0) save_iter(i, table);
    }
  }
};

Table table_first(256*4, 800);

Saver saver(5);

void glutmotion(i32 x, i32 y){
  table_first.motion(x, y);
}

void glutdisplay(){
  table_first.display();
}

void glutkeyboard(unsigned char key, i32 x, i32 y){
  table_first.keyboard(key, x, y);
}

void timer1(int){
  table_first.display();

  table_first.spin_reversing();

  glutTimerFunc(10, timer1, 0);
}

void glutsave(int){
  saver.steps++;
  saver.save(&table_first);

  glutTimerFunc(1, glutsave, 0);
}

int main(int argc, char *argv[]) {
  glutInit(& argc, argv);


  try{
    table_first.display_initialization();
    table_first.lattice_initialization();
  }
  catch (i32 i){
    switch(i){
      case 1:
      {
        std::cerr << "Failed to connect keyboard\n";
        return 0;
      }
      case 2:
      {
        std::cerr << "Failed to connect keyboard\n";
        return 0;
      }
    }
    std::cerr << "Undefined failure has occured\n";
  }

  glutDisplayFunc(glutdisplay);
  glutKeyboardFunc(glutkeyboard);
  glutMotionFunc(glutmotion);

  glutTimerFunc(1, timer1, 0);
  glutTimerFunc(1, glutsave, 0);

  glutMainLoop();

  return 0;
}
