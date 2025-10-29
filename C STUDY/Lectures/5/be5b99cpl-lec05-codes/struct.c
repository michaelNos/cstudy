#include <stdio.h>
#include <string.h>

struct record {
   int number;
   double value;
};

struct record_packed {
   int n;
   double v;
} __attribute__((packed));

void print_record(struct record rec)
{
   printf("record: number(%d), value(%lf)\n", 
         rec.number,  rec.value);
}

typedef struct {
   int n;
   double v;
} item;

typedef struct __attribute__((packed)) {
   int n;
   double v;
} item_packed;

void print_item(item *v) 
{
   printf("item: n(%d), v(%lf)\n", v->n, v->v); 
}

int main(int argc, char *argv[]) 
{
   printf("Size of int: %lu size of double: %lu\n", sizeof(int), sizeof(double));
   printf("Size of record: %lu\n", sizeof(struct record));
   printf("Size of item: %lu\n", sizeof(item));
   printf("Size of record_packed: %lu\n", sizeof(struct record_packed));
   printf("Size of item_packed: %lu\n", sizeof(item_packed));

   struct record r;
   item i = { 1, 2.3 };
   r.number = 7;
   r.value = 21.4;

   print_record(r);
   print_item(&i);
   // i = r; /* It is not allowed to assign structures of the different type */
   if (sizeof(i) == sizeof(r)) {
      print_record(r);
      printf("Size of i and r is the same, perform direct memory copy\n");
      memcpy(&i, &r, sizeof(i));
      print_item(&i);
   }

   printf("\nr2:\n");
   struct record r2 = { .value = 10.4 }; // partial initialization
   print_record(r2);

   printf("\nrec1 and rec2\n");

   struct record rec1 = { 10, 7.12 };
   struct record rec2 = { 5, 13.1 };
   print_record(rec1);
   print_record(rec2);

   rec1 = rec2;
   print_record(rec1);

   return 0;
}

// Size of int: 4 size of double: 8
// Size of record: 16
// Size of item: 16
// Size of record_packed: 12
// Size of item_packed: 12
// record: number(7), value(21.400000)
// item: n(1), v(2.300000)
// record: number(7), value(21.400000)
// Size of i and r is the same, perform direct memory copy
// item: n(7), v(21.400000)

// r2:
// record: number(0), value(10.400000)

// rec1 and rec2
// record: number(10), value(7.120000)
// record: number(5), value(13.100000)
// record: number(5), value(13.100000)
