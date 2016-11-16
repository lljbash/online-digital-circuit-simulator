--- BEGIN_PIN_INFO ---

--- EN1_1 in ---
--- A1_2 in ---
--- D13_3 in ---
--- D12_4 in ---
--- D11_5 in ---
--- D10_6 in ---
--- Y1_7 out ---
--- GND_8 gnd ---
--- Y2_9 out ---
--- D20_10 in ---
--- D21_11 out ---
--- D22_12 out ---
--- D23_13 out ---
--- A0_14 out ---
--- EN2_15 out ---
--- VCC_16 vcc ---

--- END_PIN_INFO ---

--- BEGIN_CODE ---

LIBRARY IEEE; 
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity MOD_74LS253 is
--- BEGIN_PORT_DEF ---
port(
    EN1_1, A1_2, D13_3, D12_4, D11_5, D10_6, D20_10, D21_11, D22_12, D23_13, A0_14, EN2_15: in std_logic;
    Y1_7, Y2_9: out std_logic
);
--- END_PORT_DEF ---
end MOD_74LS253;

architecture MOD_74LS253_behv of MOD_74LS253 is

signal en1, en2, d13, d12, d11, d10, d23, d22, d21, d20, a1, a0: std_logic;
signal y1, y2: std_Logic;

begin

    en1 <= EN1_1;
    en2 <= EN2_15;
    d13 <= D13_3;
    d12 <= D12_4;
    d11 <= D11_5;
    d10 <= D10_6;
    d23 <= D23_13;
    d22 <= D22_12;
    d21 <= D21_11;
    d20 <= D20_10;
    a1 <= A1_2;
    a0 <= A0_14;

    process(en1, d13, d12, d11, d10, a1, a0)
    begin 
        if(en1 = '1') then y1 = 'Z';
        elsif en1 = '0' 
            if a1 = '0' and a0 = '0' and d10 = '0' then y1 = '0';
            elsif a1 = '0' and a0 = '0' and d10 ='1' then y1 = '1';
            elsif a1 = '0' and a0 = '1' and d11 ='0' then y1 = '0';
            elsif a1 = '0' and a0 = '1' and d11 ='1' then y1 = '1';
            elsif a1 = '1' and a0 = '0' and d12 ='0' then y1 = '0';
            elsif a1 = '1' and a0 = '0' and d12 ='1' then y1 = '1';
            elsif a1 = '1' and a0 = '1' and d13 ='0' then y1 = '0';
            elsif a1 = '1' and a0 = '1' and d13 ='1' then y1 = '1';
            end if;
        end if;

    end process;

    process(en2, d23, d22, d21, d20, a1, a0)
    begin 
        if(en2 = '1') then y2 = 'Z';
        elsif en2 = '0' 
            if a1 = '0' and a0 = '0' and d20 = '0' then y2 = '0';
            elsif a1 = '0' and a0 = '0' and d20 ='1' then y2 = '1';
            elsif a1 = '0' and a0 = '1' and d21 ='0' then y2 = '0';
            elsif a1 = '0' and a0 = '1' and d21 ='1' then y2 = '1';
            elsif a1 = '1' and a0 = '0' and d22 ='0' then y2 = '0';
            elsif a1 = '1' and a0 = '0' and d22 ='1' then y2 = '1';
            elsif a1 = '1' and a0 = '1' and d23 ='0' then y2 = '0';
            elsif a1 = '1' and a0 = '1' and d23 ='1' then y2 = '1';
            end if;
        end if;

    end process;

    Y1_7 <= y1;
    Y2_9 <= y2;


end MOD_74LS253_behv;

--- END_CODE ---
