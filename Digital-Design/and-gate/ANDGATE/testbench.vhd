library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity AND_GATE_TB is
end AND_GATE_TB;

architecture Test of AND_GATE_TB is
    -- Component Declaration
    component AND_GATE
        Port (
            A : in  STD_LOGIC;
            B : in  STD_LOGIC;
            Y : out STD_LOGIC
        );
    end component;

    -- Signal Declaration
    signal A : STD_LOGIC := '0';
    signal B : STD_LOGIC := '0';
    signal Y : STD_LOGIC;

begin
    -- Component Instantiation
    DUT: AND_GATE port map (
        A => A,
        B => B,
        Y => Y
    );

    -- Test Process
    process
    begin
        -- Test Case 1: A='0', B='0'
        A <= '0'; B <= '0'; wait for 10 ns;

        -- Test Case 2: A='0', B='1'
        A <= '0'; B <= '1'; wait for 10 ns;

        -- Test Case 3: A='1', B='0'
        A <= '1'; B <= '0'; wait for 10 ns;

        -- Test Case 4: A='1', B='1'
        A <= '1'; B <= '1'; wait for 10 ns;

         A <= '0'; B <= '0'; wait for 10 ns;
        wait;
    end process;
end Test;