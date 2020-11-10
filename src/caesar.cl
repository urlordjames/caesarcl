__kernel void caesar(__global char stringin[], __constant int* shift) {
  char letter = stringin[get_global_id(0)];
  char iscap = 1;
  if (letter >= 'a' && letter <= 'z') {
    iscap = 0;
    letter -= 32;
  }
  if (!(letter >= 'A' && letter <= 'Z')) return;
  letter -= 65;
  letter = (letter + *shift) % 26;
  if (iscap == 0) {
    letter += 32;
  }
  letter += 65;
  stringin[get_global_id(0)] = letter;
}
