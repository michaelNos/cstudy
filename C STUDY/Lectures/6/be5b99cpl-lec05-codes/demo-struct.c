#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum weekdays { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY };

typedef struct {
   char *name;
   char *abbr; // abbreviation
} week_day_s;

const week_day_s days_en[] = {
   [MONDAY] = { "Monday", "mon" },
   [TUESDAY] = { "Tuesday", "tue" },
   [WEDNESDAY] = { "Wednesday", "wed" },
   [THURSDAY] = { "Thursday", "thr" },
   [FRIDAY] = { "Friday", "fri" },
};

const week_day_s days_cs[] = {
   [MONDAY] = { "Pondělí", "po" },
   [TUESDAY] = { "Úterý", "út" },
   [WEDNESDAY] = { "Středa", "st" },
   [THURSDAY] = { "Čtvrtek", "čt" },
   [FRIDAY] = { "Pátek", "pá" },
};

int main(int argc, char *argv[], char **envp)
{
   int day_of_week = argc > 1 ? atoi(argv[1]) : 1;
   if (day_of_week < 1 || day_of_week > 5) {
      fprintf(stderr, "(EE) File: '%s' Line: %d -- Given day of week out of range\n", __FILE__, __LINE__);
      return 101;
   }
   day_of_week -= 1; // start from 0

   _Bool cz = 0;
   while (*envp != NULL) {
      if (strstr(*envp, "LC_CTYPE") && strstr(*envp, "cs")) {
         cz = 1;
         break;
      }
      envp++;
   }
   const week_day_s *days = cz ? days_cs : days_en;
   printf("%d %s %s\n", day_of_week, days[day_of_week].name, days[day_of_week].abbr);
   return 0;
}
