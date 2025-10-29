#include <stdio.h>

// ===== Task 1: Struct + Enum =====
enum Department { IT, HR, SALES };

struct Employee {
    char name[30];
    int age;
    enum Department dept;
};

const char* dept_to_str(enum Department d) {
    switch (d) {
        case IT: return "IT";
        case HR: return "HR";
        case SALES: return "Sales";
        default: return "Unknown";
    }
}

// ===== Task 2: Union + Bit Fields =====
union Register {
    unsigned int raw;
    struct {
        unsigned int enable   : 1;
        unsigned int mode     : 2;
        unsigned int error    : 1;
        unsigned int reserved : 28;
    } bits;
};

// ===== Task 3: Preprocessor + Conditional Compilation =====
#define DEBUG 1

int main() {
    struct Employee e[3];
    printf("Enter info for 3 employees:\n");
    for (int i = 0; i < 3; i++) {
        printf("\nEmployee %d:\n", i + 1);
        printf("Name: ");
        scanf("%29s", e[i].name);
        printf("Age: ");
        scanf("%d", &e[i].age);
        printf("Department (0=IT,1=HR,2=Sales): ");
        scanf("%d", (int*)&e[i].dept);
    }

    printf("\n%-15s %-5s %-10s\n", "Name", "Age", "Department");
    for (int i = 0; i < 3; i++)
        printf("%-15s %-5d %-10s\n", e[i].name, e[i].age, dept_to_str(e[i].dept));

    // Task 2
    union Register reg;
    printf("\nEnter register value in hex (e.g., 0xA): ");
    scanf("%x", &reg.raw);
    printf("Enable: %u | Mode: %u | Error: %u\n", reg.bits.enable, reg.bits.mode, reg.bits.error);

    // Task 3
#ifdef DEBUG
    printf("[DEBUG] Raw register value = 0x%X\n", reg.raw);
#endif

    return 0;
}