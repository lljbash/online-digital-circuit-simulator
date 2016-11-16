--- BEGIN_PIN_INFO ---

--- EN1_1 in ---
--- A1_2 in ---
--- Y1_3 out ---
--- EN2_4 in ---
--- A2_5 in ---
--- Y2_6 out ---
--- GND_7 gnd ---
--- Y3_8 out ---
--- A3_9 in ---
--- EN3_10 in ---
--- Y4_11 out ---
--- A4_12 in ---
--- EN4_13 in ---
--- VCC_14 vcc ---

--- END_PIN_INFO ---

--- BEGIN_CODE ---

LIBRARY IEEE; 
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity MOD_74LS125 is
--- BEGIN_PORT_DEF ---
port(
    EN1_1, A1_2, EN2_4, A2_5, A3_9, EN3_10, A4_12, EN4_13: in std_logic;
    Y1_3, Y2_6, Y3_8, Y4_11: out std_logic
);
--- END_PORT_DEF ---
end MOD_74LS125;

architecture MOD_74LS125_behv of MOD_74LS125 is

signal en1, en2, en3, en4, a1, a2, a3, a4,: std_logic;
signal y1, y2, y3, y4: std_logic;

begin

    en1 <= EN1_1;
    en2 <= EN2_4;
    en3 <= EN3_10;
    en4 <= EN4_13;
    a1 <= A1_2;
    a2 <= A2_5;
    a3 <= A3_9;
    a4 <= A4_12;

    process(en1, a1)
    begin

        if en1 = '0' and a1 = '0' then y1 <= '0';
        elsif en1 = '0' and a1 = '1' then y1 <= '1';
        elsif en1 = '1' then y1 <= 'Z';
        end if;

    end process;

    process(en2, a2)
    begin

        if en2 = '0' and a2 = '0' then y2 <= '0';
        elsif en2 = '0' and a2 = '1' then y2 <= '1';
        elsif en2 = '1' then y2 <= 'Z';
        end if;

    end process;

    process(en3, a3)
    begin

        if en3 = '0' and a3 = '0' then y3 <= '0';
        elsif en3 = '0' and a3 = '1' then y3 <= '1';
        elsif en3 = '1' then y3 <= 'Z';
        end if;

    end process;

    process(en4, a4)
    begin

        if en4 = '0' and a4 = '0' then y4 <= '0';
        elsif en4 = '0' and a4 <= '1' then y4 <= '1';
        elsif en4 = '1' then y4 <= 'Z';
        end if;

    end process;



    Y1_3 <= y1;
    Y2_6 <= y2;
    Y3_8 <= y3;
    Y4_11 <= y4;


end MOD_74LS125_behv;

--- END_CODE ---
