--- BEGIN_PIN_INFO ---

--- NQ1_1 in ---
--- D1_2 in ---
--- D2_3 in ---
--- CP34_4 in ---
--- VCC_5 vcc ---
--- D3_6 in ---
--- D4_7 in ---
--- NQ4_8 out ---
--- Q4_9 out ---
--- Q3_10 out ---
--- NQ3_11 out ---
--- GND_12 gnd ---
--- CP12_13 in ---
--- NQ2_14 out ---
--- Q2_15 out ---
--- Q1_16 out ---

--- END_PIN_INFO ---

--- BEGIN_CODE ---

LIBRARY IEEE; 
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity MOD_74LS75 is
--- BEGIN_PORT_DEF ---
port(
    D1_2, D2_3, D3_6, D4_7, CP34_4, CP12_13: in std_logic;
    Q1_16, Q2_15, Q3_10, Q4_9, NQ1_1, NQ2_14, NQ3_11, NQ4_8: out std_logic
);
--- END_PORT_DEF ---
end MOD_74LS75;

architecture MOD_74LS75_behv of MOD_74LS75 is

signal d1, d2, d3, d4: std_logic;
signal cur_q1, cur_nq1, cur_q2, cur_nq2, cur_q3, cur_nq3, cur_q4, cur_nq4: std_logic;

begin

    d1 <= D1_2;
    d2 <= D2_3;
    d3 <= D3_6;
    d4 <= D4_7;_

    process(d1, CP12_13)
    begin
    if CP12_13'event and CP12_13 = 1 then 
        if (d1 = '0') then cur_q1 = '0'; cur_nq1 = '1';
        elsif(d1 = '1') then cur_q1 = '1'; cur_nq1 = '0';
        end if;

    end if;
    end process;

    process(d2, CP12_13)
    begin
    if CP12_13'event and CP12_13 = 1 then 
        if (d2 = '0') then cur_q2 = '0'; cur_nq2 = '1';
        elsif(d2 = '1') then cur_q2 = '1'; cur_nq2 = '0';
        end if;

    end if;
    end process;

    process(d3, CP34_4)
    begin
    if CP34_4'event and CP34_4 = 1 then 
        if (d3 = '0') then cur_q3 = '0'; cur_nq3 = '1';
        elsif(d3 = '1') then cur_q3 = '1'; cur_nq3 = '0';
        end if;

    end if;
    end process;

    process(d4, CP34_4)
    begin
    if CP34_4'event and CP34_4 = 1 then 
        if (d4 = '0') then cur_q4 = '0'; cur_nq4 = '1';
        elsif(d4 = '1') then cur_q4 = '1'; cur_nq4 = '0';
        end if;

    end if;
    end process;

    Q1_16 <= cur_q1;
    NQ1_1 <= cur_nq1;
    Q2_15 <= cur_q2;
    NQ2_14 <= cur_nq2;
    Q3_10 <= cur_q3;
    NQ3_11 <= cur_nq3;
    Q4_9 <= cur_q4;
    NQ4_8 <= cur_nq4;


end MOD_74LS75_behv;

--- END_CODE ---
