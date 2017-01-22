#include <iostream>

// We need to include fstream so we can use std::ofstream.
#include <fstream>

/*
 * These are the file we'll write to.  The first one will be overwritten, and
 * the second one will be appended to.
 */
#define FILENAME_OVERWRITE "people-to-overwrite.txt"
#define FILENAME_APPEND "people-to-append-to.txt"

/*
 * We'll use this structure to hold data about people we're writing to file.
 */
struct person {
  std::string first_name;
  std::string last_name;
  std::string job;
  int age;
};

int main(int argc, char** argv) {

  /*
   * This structure holds the data we'll write to file.
   */
  struct person p = {
    .first_name = "Darth",
    .last_name = "Vader",
    .job = "Imperial-Lord",
    .age = 40
  };

  /*
   * To write to a file, the very first thing we need to do is instantiate
   * a new std::ofstream and then use its .open() method to open the file we
   * want to write to.  The first argument to .open() is the path to the file
   * you want to write to.  The second (optional) argument specifies how you
   * want to write to the file.  By default (if you don't pass a second
   * argument), the file is truncated.  That means that, if the file exists
   * and has any content, that content will be deleted and overwritten with
   * whatever we write to the file.  We'll see below how to pass a different
   * argument to append to the file instead.
   *
   * Before and after running the program, check the contents of the file
   * we're using here to verify that they are, indeed, overwritten.
   */
  std::ofstream outfile;
  outfile.open(FILENAME_OVERWRITE);

  /*
   * As when opening a file to read, it's important to make sure we succeeded
   * in opening our file to which to write.  Here, we do that with the .fail()
   * method of std::ofstream.  If opening the file failed for some reason,
   * .fail() will return true.  If that's the case here, we report the error
   * and exit the program with an error status.  You could use std::ofstream's
   * .is_open() method in a similar manner to make sure the call to .open()
   * succeeded.
   */
  if (outfile.fail()) {
    std::cout << "Failed to open file." << std::endl;
    return 1;
  }

  /*
   * We write data to the file using syntax like we'd use to write something
   * to std::cout.  Here, we send data into our std::ofstream instead.
   */
  outfile << p.first_name << " " << p.last_name << " " << p.job << " " << p.age
    << std::endl;

  /*
   * It's important to call std::ofstream's .close() method to make sure all
   * of the data we've written is flushed to disk.
   */
  outfile.close();

  /*
   * Here, we're going to write data pretty much as we did above, except this
   * time, instead of truncating and overwriting the file, we're going to
   * append to it.  We do this by passing std::ofstream::app as the second
   * argument to .open.
   *
   * Before and after running the program, check the contents of the file
   * we're using here to verify that they are, indeed, still there after the
   * program runs and that the new data we write is appended to the end of the
   * file.
   */
  outfile.open(FILENAME_APPEND, std::ofstream::app);
  if (outfile.fail()) {
    std::cout << "Failed to open file." << std::endl;
    return 1;
  }
  outfile << p.first_name << " " << p.last_name << " " << p.job << " " << p.age
    << std::endl;
  outfile.close();
}
