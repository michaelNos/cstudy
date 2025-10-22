#include <stdio.h>

int main() {
    int choice;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Task 1 - While loop sum\n");
        printf("2. Task 2 - Do-while sum (stop if >25)\n");
        printf("3. Task 3 - Date to words\n");
        printf("0. Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                int num, total = 0;
                printf("Enter a number (0 to quit): ");
                scanf("%d", &num);
                while (num != 0) {
                    total += num;
                    printf("Total = %d\n", total);
                    printf("Enter a number (0 to quit): ");
                    scanf("%d", &num);
                }
                printf("Program ended.\n");
                break;
            }

            case 2: {
                int num, total = 0;
                do {
                    printf("Enter a number (0 to quit): ");
                    scanf("%d", &num);
                    total += num;
                    printf("Total = %d\n", total);
                } while (num != 0 && total <= 25);
                printf("Program ended.\n");
                break;
            }

            case 3: {
                int year, month, day;
                printf("Enter date (YYYY-MM-DD): ");
                scanf("%d-%d-%d", &year, &month, &day);

                printf("%d", day);
                if (day == 1 || day == 21 || day == 31) printf("st ");
                else if (day == 2 || day == 22) printf("nd ");
                else if (day == 3 || day == 23) printf("rd ");
                else printf("th ");

                switch (month) {
                    case 1:  printf("January "); break;
                    case 2:  printf("February "); break;
                    case 3:  printf("March "); break;
                    case 4:  printf("April "); break;
                    case 5:  printf("May "); break;
                    case 6:  printf("June "); break;
                    case 7:  printf("July "); break;
                    case 8:  printf("August "); break;
                    case 9:  printf("September "); break;
                    case 10: printf("October "); break;
                    case 11: printf("November "); break;
                    case 12: printf("December "); break;
                    default: printf("Invalid month "); break;
                }

                printf("%d\n", year);
                break;
            }

            default:
                printf("Invalid choice!\n");
        }
    }

    printf("Goodbye!\n");
    return 0;
}
