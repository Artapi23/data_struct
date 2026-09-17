library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- 16-to-1 Multiplexer with individual data and select pins
entity design is
    Port (
        d0, d1, d2, d3, d4, d5, d6, d7 : in STD_LOGIC;
        d8, d9, d10, d11, d12, d13, d14, d15 : in STD_LOGIC;
        s3, s2, s1, s0 : in STD_LOGIC;
        y : out STD_LOGIC
    );
end design;

architecture Behavioral of design is
begin
    process (d0, d1, d2, d3, d4, d5, d6, d7,
             d8, d9, d10, d11, d12, d13, d14, d15,
             s3, s2, s1, s0)
    begin
        case (s3 & s2 & s1 & s0) is
            when "0000" => y <= d0;
            when "0001" => y <= d1;
            when "0010" => y <= d2;
            when "0011" => y <= d3;
            when "0100" => y <= d4;
            when "0101" => y <= d5;
            when "0110" => y <= d6;
            when "0111" => y <= d7;
            when "1000" => y <= d8;
            when "1001" => y <= d9;
            when "1010" => y <= d10;
            when "1011" => y <= d11;
            when "1100" => y <= d12;
            when "1101" => y <= d13;
            when "1110" => y <= d14;
            when "1111" => y <= d15;
            when others => y <= 'X';
        end case;
    end process;
end Behavioral;
