--- BEGIN_PIN_INFO ---

--- CLK5_1 in ---
--- R1_2 in ---
--- R2_3 in ---
--- NC_4 nc ---
--- VCC_5 vcc ---
--- S1_6 in ---
--- S2_7 in ---
--- Q2_8 out ---
--- Q1_9 out ---
--- GND_10 gnd ---
--- Q3_11 out ---
--- Q0_12 out ---
--- NC_13 nc ---
--- CLK2_14 in ---

--- END_PIN_INFO ---

--- BEGIN_CODE ---

LIBRARY IEEE; 
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity MOD_74LS90 is
--- BEGIN_PORT_DEF ---
port(
    CLK5_1, CLK2_14, R1_2, R2_3, S1_6, S2_7: in std_logic;
    Q0_12, Q1_9, Q2_8, Q3_11: out std_logic
);
--- END_PORT_DEF ---
end MOD_74LS90;

architecture MOD_74LS90_behv of MOD_74LS90 is

signal num2: integer range 0 to 1 := 0;
signal num5: integer range 0 to 5 := 0;

signal r1, r2, s1, s2: std_logic;
signal cur_q1, cur_q2, cur_q3, cur_q4: std_logic;

begin

    r1 <= R1_2;
    r2 <= R2_3;
    s1 <= S1_6;
    s2 <= S2_7;

    process(r1, r2, s1, s2, CLK2_14, CLK5_1)
    begin
    if CLK2_14'event and CLK2_14 = '1' then 
        if r1 = '1' and r2 = '1' and s1 = '0' then cur_q1 <= '0'; cur_q2 <= '0'; cur_q3 <= '0'; cur_q4 <= '0';
        elsif r1 = '1' and r2 = '1' and s2 = '0' then cur_q1 <= '0'; cur_q2 <= '0'; cur_q3 <= '0'; cur_q4 <= '0';
        elsif s1 = '1' and s2 = '1' then cur_q1 <= '1'; cur_q2 <= '0'; cur_q3 <= '0'; cur_q4 <= '1';
        elsif (r2 = '0' and s2 = '0') or (r1 = '0' and s1 = '0') then
            if(num2 = 1) then
                cur_q1 <= '0';
                num2 <= 0;
            else 
                cur_q1 <= '1';
                num2 <= num2 + 1;
            end if;
        end if;

    end if;
     
     if CLK5_1'event and CLK5_1 = '1' then 
        if r1 = '1' and r2 = '1' and s1 = '0' then cur_q1 <= '0'; cur_q2 <= '0'; cur_q3 <= '0'; cur_q4 <= '0';
        elsif r1 = '1' and r2 = '1' and s2 = '0' then cur_q1 <= '0'; cur_q2 <= '0'; cur_q3 <= '0'; cur_q4 <= '0';
        elsif s1 = '1' and s2 = '1' then cur_q1 <= '1'; cur_q2 <= '0'; cur_q3 <= '0'; cur_q4 <= '1';
        elsif (r2 = '0' and s2 = '0') or (r1 = '0' and s1 = '0') then
            if(num5 = 5) then
                cur_q2 <= '0';
                cur_q3 <= '0';
                cur_q4 <= '0';
                num5 <= 0;
            elsif(num5 = 0) then
                cur_q2 <= '1';
                cur_q3 <= '0';
                cur_q4 <= '0';
                num5 <= num5 + 1;
            elsif(num5 = 1) then
                cur_q2 <= '0';
                cur_q3 <= '1';
                cur_q4 <= '0';
                num5 <= num5 + 1;
            elsif(num5 = 2) then
                cur_q2 <= '0';
                cur_q3 <= '1';
                cur_q4 <= '0';
                num5 <= num5 + 1;
            elsif(num5 = 3) then
                cur_q2 <= '1';
                cur_q3 <= '1';
                cur_q4 <= '0';
                num5 <= num5 + 1;
            elsif(num5 = 4) then
                cur_q2 <= '0';
                cur_q3 <= '0';
                cur_q4 <= '1';
                num5 <= num5 + 1;
            end if;
        end if;

    end if;
    end process;



    

    Q0_12 <= cur_q1;
    Q1_9 <= cur_q2;
    Q2_8 <= cur_q3;
    Q3_11 <= cur_q4;


end MOD_74LS90_behv;

--- END_CODE ---
