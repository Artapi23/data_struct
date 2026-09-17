library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity seven_segment is
  port (
    D0 : in std_logic;
    D1 : in std_logic;
    D2 : in std_logic;
    D3 : in std_logic;
    D4 : in std_logic;
    D5 : in std_logic;
    D6 : in std_logic;
    D7 : in std_logic;
    D8 : in std_logic;
    D9 : in std_logic;

    seg_a : out std_logic;
    seg_b : out std_logic;
    seg_c : out std_logic;
    seg_d : out std_logic;
    seg_e : out std_logic;
    seg_f : out std_logic;
    seg_g : out std_logic
  );
end seven_segment;

architecture Behavioral of seven_segment is

  -- Encoder Outputs
  signal D, C, B, A : std_logic;

  -- Inverted Signals
  signal ND, NC, NB, NA : std_logic;

  -- Decoder Outputs
  signal a_dec, b_dec, c_dec : std_logic;
  signal d_dec, e_dec, f_dec : std_logic;
  signal g_dec               : std_logic;

  -- Enable Signal (OR 5 Input)
  signal EN : std_logic;

begin

  --------------------------------------------------
  -- Encoder
  --------------------------------------------------

  D <= D8 or D9;
  C <= D4 or D5 or D6 or D7;
  B <= D2 or D3 or D6 or D7;
  A <= D1 or D3 or D5 or D7 or D9;

  --------------------------------------------------
  -- NOT Gates
  --------------------------------------------------

  NA <= not A;
  NB <= not B;
  NC <= not C;
  ND <= not D;

  --------------------------------------------------
  -- OR 5 Input
  -- D0 + A + B + C + D
  --------------------------------------------------

  EN <= D0 or A or B or C or D;

  --------------------------------------------------
  -- Decoder Logic
  --------------------------------------------------

  a_dec <= D or B or (NC and NA) or (C and A) ;
  b_dec <= Nc or (B AND A) or (NB AND NA);
  c_dec <= NB or C or A;
  d_dec <= (NC and B) or D or (NA AND NC) or (B AND NA) or (C and NB and A);
  e_dec <= (B and NA) or (NC and NA);
  f_dec <= D or (C and NA) or (C and NB) or (NB and NA);  
  g_dec <= D or (B and NA) or (NC and B) or (C and NB);

  --------------------------------------------------
  -- Final AND Gates
  --------------------------------------------------

  seg_a <= a_dec and EN;
  seg_b <= b_dec and EN;
  seg_c <= c_dec and EN;
  seg_d <= d_dec and EN;
  seg_e <= e_dec and EN;
  seg_f <= f_dec and EN;
  seg_g <= g_dec and EN;

end Behavioral;