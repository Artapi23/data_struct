library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity testbench is
end testbench;

architecture Behavioral of testbench is
    signal d0  : STD_LOGIC := '1';
    signal d1  : STD_LOGIC := '1';
    signal d2  : STD_LOGIC := '0';
    signal d3  : STD_LOGIC := '0';
    signal d4  : STD_LOGIC := '1';
    signal d5  : STD_LOGIC := '0';
    signal d6  : STD_LOGIC := '1';
    signal d7  : STD_LOGIC := '0';
    signal d8  : STD_LOGIC := '0';
    signal d9  : STD_LOGIC := '0';
    signal d10 : STD_LOGIC := '1';
    signal d11 : STD_LOGIC := '1';
    signal d12 : STD_LOGIC := '0';
    signal d13 : STD_LOGIC := '1';
    signal d14 : STD_LOGIC := '0';
    signal d15 : STD_LOGIC := '1';
    signal s3, s2, s1, s0 : STD_LOGIC := '0';
    signal select_value : STD_LOGIC_VECTOR(3 downto 0) := "0000";
    signal y : STD_LOGIC;
begin
    s3 <= select_value(3);
    s2 <= select_value(2);
    s1 <= select_value(1);
    s0 <= select_value(0);

    uut: entity work.design(Behavioral)
        port map (
            d0 => d0, d1 => d1, d2 => d2, d3 => d3,
            d4 => d4, d5 => d5, d6 => d6, d7 => d7,
            d8 => d8, d9 => d9, d10 => d10, d11 => d11,
            d12 => d12, d13 => d13, d14 => d14, d15 => d15,
            s3 => s3, s2 => s2, s1 => s1, s0 => s0,
            y => y
        );

    stimulus: process
    begin
        for i in 0 to 15 loop
            select_value <= STD_LOGIC_VECTOR(to_unsigned(i, 4));
            wait for 10 ns;
        end loop;
        wait;
    end process;
end Behavioral;
