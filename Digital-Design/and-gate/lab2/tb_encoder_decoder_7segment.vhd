library IEEE;
use IEEE.std_logic_1164.all;

entity tb_encoder_decoder_7segment is
end entity tb_encoder_decoder_7segment;

architecture tb of tb_encoder_decoder_7segment is
  constant PULSE : time := 1 us;
  signal D0 : std_logic := '0';
  signal D1 : std_logic := '0';
  signal D2 : std_logic := '0';
  signal D3 : std_logic := '0';
  signal D4 : std_logic := '0';
  signal D5 : std_logic := '0';
  signal D6 : std_logic := '0';
  signal D7 : std_logic := '0';
  signal D8 : std_logic := '0';
  signal D9 : std_logic := '0';

  signal seg_a : std_logic;
  signal seg_b : std_logic;
  signal seg_c : std_logic;
  signal seg_d : std_logic;
  signal seg_e : std_logic;
  signal seg_f : std_logic;
  signal seg_g : std_logic;
begin
  UUT : entity work.seven_segment
  port map
  (
    D0 => D0,
    D1 => D1,
    D2 => D2,
    D3 => D3,
    D4 => D4,
    D5 => D5,
    D6 => D6,
    D7 => D7,
    D8 => D8,
    D9 => D9,

    seg_a => seg_a,
    seg_b => seg_b,
    seg_c => seg_c,
    seg_d => seg_d,
    seg_e => seg_e,
    seg_f => seg_f,
    seg_g => seg_g
  );
  stimulus : process
  begin
    D0 <= '1';
        wait for PULSE;
    D0 <= '0';

    D1 <= '1';
        wait for PULSE;
    D1 <= '0';

    D2 <= '1';
        wait for PULSE;
    D2 <= '0';

    D3 <= '1';
        wait for PULSE;
    D3 <= '0';

    D4 <= '1';
        wait for PULSE;
    D4 <= '0';

    D5 <= '1';
        wait for PULSE;
    D5 <= '0';

    D6 <= '1';
        wait for PULSE;
    D6 <= '0';

    D7 <= '1';
        wait for PULSE;
    D7 <= '0';

    D8 <= '1';
        wait for PULSE;
    D8 <= '0';

    D9 <= '1';
        wait for PULSE;
    D9 <= '0';

        wait;
  end process;
end architecture tb;