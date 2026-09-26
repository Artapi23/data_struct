library IEEE;
use IEEE.std_logic_1164.all;

entity comparator is
port(
    A3, A2, A1 : in  std_logic;
    B3, B2, B1 : in  std_logic;

    A_L_B : out std_logic;
    A_E_B : out std_logic;
    A_M_B : out std_logic
);
end comparator;

architecture rtl of comparator is

    signal L0, L1, L2, L3 : std_logic;
    signal E0, E1, E2, E3 : std_logic;
    signal M0, M1, M2, M3 : std_logic;

begin
    -- A>B
    L0 <= not B1 and A1 and not B3 and not B2;
    L1 <= (A1 and not B3 and B2 and not B1) or (not B3 and not B2);
    L2 <= not B3 or (A1 and B3 and not B2 and not B1);
    L3 <= not B3 or (B3 and not B2) or (A1 and not B1);

    A_L_B <= (L0 and not A3 and not A2) or
             (L1 and not A3 and A2) or
             (L2 and A3 and not A2) or
             (L3 and A3 and A2);
    -- End A>B

    -- A=B
    E0 <= (not B3 and not B2) and (A1 xnor B1);
    E1 <= (not B3 and B2) and (A1 xnor B1);
    E2 <= (B3 and not B2) and (A1 xnor B1);
    E3 <= (B3 and B2) and (A1 xnor B1);

    A_E_B <= (E0 and not A3 and not A2) or
             (E1 and not A3 and A2) or
             (E2 and A3 and not A2) or
             (E3 and A3 and A2);
    -- End A=B

    -- A<B
    M0 <= (not A1 and not B3 and not B2 and B1) or (B2 or B3);
    M1 <= (not A1 and not B3 and B2 and B1) or B3;
    M2 <= B3 and (B2 or (not A1 and not B2 and B1));
    M3 <= not A1 and B3 and B2 and B1;

    A_M_B <= (M0 and not A3 and not A2) or
             (M1 and not A3 and A2) or
             (M2 and A3 and not A2) or
             (M3 and A3 and A2);
    -- End A<B

end rtl;