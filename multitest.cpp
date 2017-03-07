#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{
    // Invoke the Java program with the passed arguments.
    string cmd = "java -cp OthelloFramework.jar TestGame";    
    argv++;
    while (--argc) {
        cmd += " ";
        cmd += *(argv++);
    }
    /* 
     * Runs testgame 10 times in a row with a new test being started when the previous
     * game window is closed
     */
    for (int i = 0; i < 10; i ++)
    {
    	system(cmd.c_str());
    }
    return 0;
}