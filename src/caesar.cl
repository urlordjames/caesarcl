__kernel void caesar(__global char stringin[], __constant int shift[]) {
  char letter = stringin[get_global_id(0)];
  if (letter == ' ') return;
  char iscap = 1;
  if (letter >= 'a' && letter <= 'z') {
    iscap = 0;
    letter -= 32;
  }
  letter += shift[0] % 26;
  if (iscap == 0) {
    letter += 32;
  }
  stringin[get_global_id(0)] = letter;
}
