--- BEGIN_PIN_INFO ---

--- R1_1 in ---
--- D1_2 in ---
--- CP1_3 in ---
--- S1_4 in ---
--- Q1_5 out ---
--- NQ1_6 out ---
--- GND_7 gnd ---
--- NQ2_8 out ---
--- Q2_9 out ---
--- S2_10 in ---
--- CP2_11 in ---
--- D2_12 in ---
--- R2_13 in ---
--- VCC_14 vcc ---

--- END_PIN_INFO ---

--- BEGIN_CODE ---

LIBRARY IEEE; 
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity MOD_74LS74 is
--- BEGIN_PORT_DEF ---
port(
    R1_1, R2_13, D1_2, D2_12, CP1_3, CP2_11, S1_4, S2_10: in std_logic;
    Q1_5, Q2_9, NQ1_6, NQ2_8: out std_logic
);
--- END_PORT_DEF ---
end MOD_74LS74;

architecture MOD_74LS74_behv of MOD_74LS74 is

signal sr1, sr2: std_logic_vector(1 downto 0);
signal cur_q1, cur_nq1, cur_q2, cur_nq2: std_logic;

begin

    sr1 <= S1_4 & R1_1;
    sr2 <= S2_10 & R2_13;

    process(D1_2, sr1, CP1_3)
    begin
    if(sr1 = '01') then cur_q1 = '1'; cur_nq1 = '0';
    elsif(sr1 = '10') then cur_q1 = '0'; cur_nq1 = '1';
    elsif(sr1 = '00') then cur_q1 = '1'; cur_nq1 = '1';
    elsif CP1_3'event and CP1_3 = 1 then cur_q1 = D1_2; cur_nq1 = not D1_2;

    end if;
    end process;

    process(D2_12, sr2, CP2_11)
    begin
    if(sr2 = '01') then cur_q2 = '1'; cur_nq2 = '0';
    elsif(sr2 = '10') then cur_q2 = '0'; cur_nq2 = '1';
    elsif(sr2 = '00') then cur_q2 = '1'; cur_nq2 = '1';
    elsif CP2_11'event and CP2_11 = 1 then cur_q2 = D2_12; cur_nq2 = not D2_12;

    end if;
    end process;

    Q1_5 <= cur_q1;
    NQ1_6 <= cur_nq1;
    Q2_9 <= cur_q2;
    NQ2_8 <= cur_nq2;


end MOD_74LS74_behv;

--- END_CODE ---
