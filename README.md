# PCF8574
Arduino PCF8574 library

Available commands:

setP(int P_number, int state);

- This means you can set any P (P0-P7 on PCF8574) to LOW or HIGH by using
  setP(x, LOW); or setP(x, HIGH); where x is P number.
  Or you can set all at once by replacing x with 8.


readP(int P_number);

- If set to specific P number returns just the state of it as LOW/0 or HIGH/1.
  If set to 8 returns all states at once as byte/number.

  int return_val = readP(int x);


toggleP(int P_number);

- Toggles the state of P to oposite state. 1 to 0, 0 to 1.
  Again, 8 toggles all at once.
