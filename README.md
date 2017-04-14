# PCF8574
Arduino PCF8574 library

Available commands:

If we want to control PCF8574, we need to create an instance of PCF8574:

  PCF8574 expander(EXP_ADDRESS);

  - We are creating an instance named expander for PCF8574 @ address 0b0100/A2/A1/A0, to GND = 0, to LOGIC (3,3V;5V) = 1

  Then we can use these commnads:

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


We can also wire an rotary encoderto PCF8574.
If we don't use other pins than assigned to encoder (pins A, B and BUTTON),
we don't have to create an PCF8574 instance. Just create an ENCODER instance:

  ENCODER encoder(EXP_ADDRESS, PINA, PINB, BUTTON);

    - We are creating an instance named encoder wit assigned pins A, B and BUTTON,
      wired to PCF8574 @ address 0b0100/A2/A1/A0.

  Then we can use these commnads:

  encoder.init(int state);

    - Sets pins A, B and BUTTON pin to LOW/HIGH (0/1).


  int getMovement();

    - Returns: 1 for clockwise movement
               0 for no movement
              -1 for counterclockwise


  bool getButton();

    - Returns state of button.
