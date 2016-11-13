--- BEGIN_PIN_INFO ---

--- R_1 in ---
--- CP_2 in ---
--- A_3 in ---
--- B_4 in ---
--- C_5 in ---
--- D_6 in ---
--- P_7 in ---
--- GND_8 gnd ---
--- LD_9 in ---
--- T_10 in ---
--- Q3_11 out ---
--- Q2_12 out ---
--- Q1_13 out ---
--- Q0_14 out ---
--- CO_15 out ---
--- VCC_16 vcc ---

--- END_PIN_INFO ---

--- BEGIN_CODE ---

LIBRARY IEEE; 
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity MOD_74LS161 is
--- BEGIN_PORT_DEF ---
port(
    CP_2, T_10, P_7, LD_9, R_1: in std_logic;
    D_6, C_5, B_4, A_3: in std_logic; 
    Q0_14, Q1_13, Q2_12, Q3_11: out std_logic_VECTOR; 
    CO_15: out std_logic
);
--- END_PORT_DEF ---
end MOD_74LS161;

architecture MOD_74LS161_behv of MOD_74LS161 is

signal a, b, c: std_logic;
signal D, CQI: std_logic_vector(3 downto 0); 

--signal r1, r2, s1, s2: std_logic;
--signal cur_q1, cur_q2, cur_q3, cur_q4: std_logic;

begin

    D <= D_6 & C_5 & B_4 & A_3;
    a <= T_10 and P_7; 
    b <= (not (CQI(3) and CQI(0))) and LD_9; 

    process(CP_2, T_10, P_7, LD_9, R_1, D_6, C_5, B_4, A_3)
    begin 
        if a = '1' then
            if CP_2'event and CP_2 = '1' then 
                if b = '0' then CQI <= D; 
                else CQI <= CQI + 1; 
                end if; 
            end if; 
            if CQI = 9 then c <= '1'; 
            else c <= '0'; 
            end if; 
        end if;
        if CP_2'event and CP_2 = '1' then CO_15 <= c;
        end if; 
        if R_1 = '0' then CQI <= "0000"; 
        end if;

    end process;

    D_6 <= CQI(3);
    C_5 <= CQI(2);
    B_4 <= CQI(1);
    A_3 <= CQI(0);


end MOD_74LS161_behv;

--- END_CODE ---
