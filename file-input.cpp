#include <iostream>

// We need to include fstream so we can use std::ifstream.
#include <fstream>

// We need to include string so we can use getline().
#include <string>

// This is the file we'll try to read.
#define FILENAME "people-to-read.txt"

/*
 * We'll use this structure a little later to hold data about the people we're
 * reading from the file.
 */
struct person {
  std::string first_name;
  std::string last_name;
  std::string job;
  int age;
};

int main(int argc, char** argv) {

  /*
   * To read from a file, the very first thing we need to do is instantiate
   * a new std::ifstream and then use its .open() method to open the file we
   * want to read.  The argument to .open() is the path to the file you want
   * to read.
   */
  std::ifstream infile;
  infile.open(FILENAME);

  /*
   * It's very possible that opening a file to read will fail for some reason,
   * e.g. the file doesn't actually exist.  For this reason, it's important to
   * always make sure your call to .open() succeeded.  One way to do this is
   * to use the .fail() method, like we do here.  If opening the file failed
   * for some reason, .fail() will return true.  If that's the case here, we
   * report the error and exit the program with an error status.  You could
   * use std::ifstream's .is_open() method in a similar manner to make sure
   * the call to .open() succeeded.
   */
  if (infile.fail()) {
    std::cerr << "Failed to open file." << std::endl;
    return 1;
  }

  /*
   * One important way we can read things from the file once we're sure it's
   * open is using syntax like we'd use to read from the user with std::cin.
   * Below, we try to read a string, and then we try to read an int.  Note
   * that both times, we use infile.fail() to perform error checking, making
   * sure we were able to read the values we were trying to read.
   */
  std::string str;
  infile >> str;
  if (infile.fail()) {
    std::cout << "Failed to read a string." << std::endl;
  } else {
    std::cout << "Read this string: " << str << std::endl;
  }

  /*
   * Because of the way the file we're trying to read is set up, reading an
   * integer here should fail.  Note that we use infile.clear() after the
   * failure here to clear the error so we can read more things below.  Using
   * .clear() is not typical: we're using it here only so we can continue with
   * the demonstration.
   */
  int n;
  infile >> n;
  if (infile.fail()) {
    std::cout << "Failed to read an int." << std::endl;
  } else {
    std::cout << "Read this int: " << n << std::endl;
  }
  infile.clear();

  /*
   * Another method of reading data from a file is to use the getline()
   * function (for which we need to #include <string>) to read an entire line
   * from the file.  The getline() function will read from the current
   * location of the cursor (which moves through the contents of the file to
   * keep track of how much of the file we've read so far) to the next newline
   * character ('\n').  It's good practice to do error checking here using
   * the .fail() method, just like we did above.
   */
  std::string line;
  getline(infile, line);
  if (infile.fail()) {
    std::cout << "Failed to read a line." << std::endl;
  } else {
    std::cout << "Read this line: " << line << std::endl;
  }

  /*
   * A third method for reading data from a file is to read a single character
   * using std::ifstream's .get() method.  Again, it's good practice to do
   * error checking here using the .fail() method like we did above.
   */
  char c;
  infile.get(c);
  if (infile.fail()) {
    std::cout << "Failed to read a char." << std::endl;
  } else {
    std::cout << "Read this char: " << c << std::endl;
  }

  /*
   * Usually, we don't just want to read one value, one line, or one character
   * from a file and be done with it.  We want to read everything from that
   * file.  To do that, we often use a loop of some sort.  If you know exactly
   * how many lines are in your file, you could use one or more for loops to
   * loop through the data there.  This is the case with your Assignment 1
   * (hint, hint).  If you don't know how many lines there are in the file,
   * you can use a while loop, using std::ifstream's .eof() method to figure
   * out when you've reached the end of the file.
   *
   * Within your loop, you can use any of the three methods above to read
   * data from the file.  For example, here, we loop through the file reading
   * a character at a time and making sure each read didn't fail.  Note that
   * we use std::ifstream's .seekg() method to reset the cursor to the
   * beginning of the file and the .clear() method to clear any errors or the
   * EOF flag.
   */
  infile.clear();
  infile.seekg(0);
  std::cout << "File contents, read a character at a time:";
  while (!infile.eof()) {
    infile.get(c);
    if (infile.fail()) {
      break;
    }
    std::cout << " \"" << c << "\"";
  }
  std::cout << std::endl << std::endl;

  /*
   * We can also read the file one line at a time, as we do here.
   */
  infile.clear();
  infile.seekg(0);
  std::cout << "File contents, read a line at a time:";
  while (!infile.eof()) {
    getline(infile, line);
    if (infile.fail()) {
      break;
    }
    std::cout << " \"" << line << "\"";
  }
  std::cout << std::endl << std::endl;

  /*
   * However, this file has a special structure, where each line contains
   * four known values, each separated by a space:
   *
   * first_name last_name job age
   *
   * Because we know this structure and the type of each field (all are
   * strings except for age, which is an int), we can read in the values more
   * more directly.  Here, we'll read those values directly into a structure
   * to contain them, one line at a time, using our familiar std::cin-style
   * syntax.
   */
  infile.clear();
  infile.seekg(0);
  struct person p;
  std::cout << "File contents, read a person at a time:" << std::endl;
  while (!infile.eof()) {
    infile >> p.first_name >> p.last_name >> p.job >> p.age;
    if (infile.fail()) {
      break;
    }
    std::cout << "Name: " << p.first_name << " " << p.last_name << "\tJob: "
      << p.job << "\tAge: " << p.age << std::endl;
  }

  /*
   * After reading the data from our file, it's important to call the close()
   * method on our std::ifstream to make sure all of its resources are cleaned
   * up correctly.
   */
  infile.close();
}
