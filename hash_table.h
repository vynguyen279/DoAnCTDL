#pragma once

int probing(int x) {
	return PRIME * x;
}

int hash(char* s)
{
   int h = FIRSTH;
   while (*s) {
     h = (h * A) ^ (s[0] * B);
     s++;
   }
   h %= MAXHASH;
   if(h < 0) return -1 * h;
   return h;
}
