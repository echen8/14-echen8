#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEY 429


// make_sem
// PURPOSE: Creates a semaphore, sets value to 'value'.  If semaphore already exists, prints message saying so.
// RETURN: semid
int make_sem( int value ) {

  int semid = semget( KEY, 1, IPC_CREAT | IPC_EXCL | 0777 );

  if ( semid == -1 ) {
    printf( "Semaphore already exists with ID#%d. Your requested semaphore was not created.\n", semid );
  }
  else {
    semctl( semid, 0, SETVAL, value );
    printf( "Semaphore successfully created with ID#%d.\n", semid );
  }

  return semid;
  
}


// get_value
// PURPOSE: Gets value of specified semid
// RETURN: the current semaphore value, or -1 if failed.
int get_value( int semid ) {

  int value = semctl( semid, 0, GETVAL );
  
  if ( value == -1 ) {
    if ( semid == -1 ) printf( "The semaphore does not exist! Value is unobtainable.\n" );
    else printf( "The attempt to get value of Semaphore ID#%d failed.\n", semid );
  }
  
  else printf( "Semaphore ID#%d -- Value: %d\n", semid, value );
  
  return value;

}


// rm_sem
// PURPOSE: Removes the semaphore.
// RETURN: 0 if successful, -1 if failed.
int rm_sem( int semid ) {

  int out = semctl( semid, 0, IPC_RMID );
  
  if ( out == 0 ) {
    printf( "Semaphore successfully removed.\n" );
  }
  
  else if ( out == -1 ) {
    printf( "The attempt to remove semaphore ID#%d failed.\n", semid );
  }

  return out;
}


int main( int argc, char * argv[] ) {

  // Check for -c arg
  if ( !strcmp( argv[1], "-c" ) ) make_sem( atoi( argv[2] ) );

  // Check for -v arg
  else if ( !strcmp( argv[1], "-v" ) ) get_value( semget( KEY, 0, 0777 ) );

  // Check for -r arg
  else if ( !strcmp( argv[1], "-r" ) ) rm_sem( semget( KEY, 0, 0777 ) );

  // If nothing matched
  else printf( "Unrecognized argument.  Please double check it and try again.\n" );
  

  return 0;
}

// NOTE: The return values of each function is there just in case, but the functions themselves have been programmed to handle the printing solely to make the main() function more clean.
