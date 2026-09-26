-- Testbench for 3-bit Comparator
library IEEE;
use IEEE.std_logic_1164.all;

entity testbench is
-- empty
end testbench;

architecture tb of testbench is

-- DUT component
component comparator is
port(
  A3, A2, A1: in std_logic;
  B3, B2, B1: in std_logic;

  A_L_B : out std_logic;
  A_E_B : out std_logic;
  A_M_B : out std_logic);
end component;

-- Signals
signal A3, A2, A1: std_logic;
signal B3, B2, B1: std_logic;
signal A_L_B, A_E_B, A_M_B: std_logic;

begin
  -- Connect DUT
  DUT: comparator port map(
    A3, A2, A1,
    B3, B2, B1,
    A_L_B, A_E_B, A_M_B);

  process
  begin

    -- Test A=0 (000), B=0 (000) --> A=B
    A3<='0'; A2<='0'; A1<='0';
    B3<='0'; B2<='0'; B1<='0';
    wait for 1 ns;
    assert(A_E_B='1') report "Fail: A=0,B=0 should give A=B" severity error;
    assert(A_L_B='0') report "Fail: A=0,B=0 should not give A>B" severity error;
    assert(A_M_B='0') report "Fail: A=0,B=0 should not give A<B" severity error;

    -- Test A=1 (001), B=0 (000) --> A>B
    A3<='0'; A2<='0'; A1<='1';
    B3<='0'; B2<='0'; B1<='0';
    wait for 1 ns;
    assert(A_L_B='1') report "Fail: A=1,B=0 should give A>B" severity error;

    -- Test A=0 (000), B=1 (001) --> A<B
    A3<='0'; A2<='0'; A1<='0';
    B3<='0'; B2<='0'; B1<='1';
    wait for 1 ns;
    assert(A_M_B='1') report "Fail: A=0,B=1 should give A<B" severity error;

    -- Test A=2 (010), B=2 (010) --> A=B
    A3<='0'; A2<='1'; A1<='0';
    B3<='0'; B2<='1'; B1<='0';
    wait for 1 ns;
    assert(A_E_B='1') report "Fail: A=2,B=2 should give A=B" severity error;

    -- Test A=3 (011), B=2 (010) --> A>B
    A3<='0'; A2<='1'; A1<='1';
    B3<='0'; B2<='1'; B1<='0';
    wait for 1 ns;
    assert(A_L_B='1') report "Fail: A=3,B=2 should give A>B" severity error;

    -- Test A=2 (010), B=3 (011) --> A<B
    A3<='0'; A2<='1'; A1<='0';
    B3<='0'; B2<='1'; B1<='1';
    wait for 1 ns;
    assert(A_M_B='1') report "Fail: A=2,B=3 should give A<B" severity error;

    -- Test A=4 (100), B=3 (011) --> A>B
    A3<='1'; A2<='0'; A1<='0';
    B3<='0'; B2<='1'; B1<='1';
    wait for 1 ns;
    assert(A_L_B='1') report "Fail: A=4,B=3 should give A>B" severity error;

    -- Test A=3 (011), B=4 (100) --> A<B
    A3<='0'; A2<='1'; A1<='1';
    B3<='1'; B2<='0'; B1<='0';
    wait for 1 ns;
    assert(A_M_B='1') report "Fail: A=3,B=4 should give A<B" severity error;

    -- Test A=5 (101), B=5 (101) --> A=B
    A3<='1'; A2<='0'; A1<='1';
    B3<='1'; B2<='0'; B1<='1';
    wait for 1 ns;
    assert(A_E_B='1') report "Fail: A=5,B=5 should give A=B" severity error;

    -- Test A=6 (110), B=5 (101) --> A>B
    A3<='1'; A2<='1'; A1<='0';
    B3<='1'; B2<='0'; B1<='1';
    wait for 1 ns;
    assert(A_L_B='1') report "Fail: A=6,B=5 should give A>B" severity error;

    -- Test A=5 (101), B=6 (110) --> A<B
    A3<='1'; A2<='0'; A1<='1';
    B3<='1'; B2<='1'; B1<='0';
    wait for 1 ns;
    assert(A_M_B='1') report "Fail: A=5,B=6 should give A<B" severity error;

    -- Test A=7 (111), B=7 (111) --> A=B
    A3<='1'; A2<='1'; A1<='1';
    B3<='1'; B2<='1'; B1<='1';
    wait for 1 ns;
    assert(A_E_B='1') report "Fail: A=7,B=7 should give A=B" severity error;

    -- Test A=7 (111), B=0 (000) --> A>B
    A3<='1'; A2<='1'; A1<='1';
    B3<='0'; B2<='0'; B1<='0';
    wait for 1 ns;
    assert(A_L_B='1') report "Fail: A=7,B=0 should give A>B" severity error;

    -- Test A=0 (000), B=7 (111) --> A<B
    A3<='0'; A2<='0'; A1<='0';
    B3<='1'; B2<='1'; B1<='1';
    wait for 1 ns;
    assert(A_M_B='1') report "Fail: A=0,B=7 should give A<B" severity error;

    -- Test A=5 (100), B=2 (100) --> A>B
    A3<= '1'; A2<='0'; A1<='1'; 
    B3<= '0'; B2<='1'; B1<='0'; 
    wait for 1 ns;
    assert(A_L_B='1') report "Fail: A=5,B=2 should give A>B" severity error;

    assert false report "Test done." severity note;
    wait;
  end process;
end tb;