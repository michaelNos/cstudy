#include <stdio.h>

#define USENAME_LEN 8

int main(void)
{
   struct {
      int login_count;
      char username[USENAME_LEN + 1];
      int last_login;
   } user1 = { 0, "admin", 1477134134 }, //date +%s
     user2 = { .username = "root", .login_count = 128 }; // designated initializers in C99

   printf("User1 '%s' last login on: %d\n", user1.username, user1.last_login);
   printf("User2 '%s' last login on: %d\n", user2.username, user2.last_login);

   user2 = user1; // assignment operator is defined for structures
   printf("User2 '%s' last login on: %d\n", user2.username, user2.last_login);
   return 0;
}

// User1 'admin' last login on: 1477134134
// User2 'root' last login on: 0
// User2 'admin' last login on: 1477134134
