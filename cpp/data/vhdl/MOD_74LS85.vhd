--- BEGIN_PIN_INFO ---

--- Q3_1 in ---
--- P_QIN1_2 in ---
--- P_QIN2_3 in ---
--- P_QIN3_4 in ---
--- P_QOUT1_5 out ---
--- P_QOUT2_6 out ---
--- P_QOUT3_7 out ---
--- GND_8 gnd ---
--- Q0_9 in ---
--- P0_10 in ---
--- Q1_11 in ---
--- P1_12 in ---
--- P2_13 in ---
--- Q2_14 in ---
--- P3_15 in ---
--- VCC_16 vcc ---

--- END_PIN_INFO ---

--- BEGIN_CODE ---

LIBRARY IEEE; 
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity MOD_74LS85 is
--- BEGIN_PORT_DEF ---
port(
    Q3_1, P_QIN1_2, P_QIN2_3, P_QIN3_4, Q0_9, P0_10, Q1_11, P1_12, Q2_14, P2_13, P3_15: in std_logic;
    P_QOUT1_5, P_QOUT2_6, P_QOUT3_7: out std_logic
);
--- END_PORT_DEF ---
end MOD_74LS85;

architecture MOD_74LS85_behv of MOD_74LS85 is

signal q1, q2, q3, q4, p1, p2, p3, p4: std_logic;
signal pqin1, pqin2, pqin3: std_logic;
signal pout1, pout2, pout3: std_logic;

begin

    q1 <= Q0_9;
    q2 <= Q1_11;
    q3 <= Q2_14;
    q4 <= Q3_1;
    p1 <= P0_10;
    p2 <= P1_12;
    p3 <= P2_13;
    p4 <= P3_15;
    pqin1 <= P_QIN1_2;
    pqin2 <= P_QIN2_3;
    pqin3 <= P_QIN3_4;

    process(q1, q2, q3, q4, p1, p2, p3, p4, pqin1, pqin2, pqin3)
    begin

        if(p4 > q4) then pout1 = '1'; pout3 = '0'; pout2 = '0';
        elsif(p4 < q4) then pout1 = '0'; pout3 = '1'; pout2 = '0';
        elsif(p4 = q4) then
            if(p3 > q3) then pout1 = '1'; pout3 = '0'; pout2 = '0';
            elsif(p3 < q3) then pout1 = '0'; pout3 = '1'; pout2 = '0';
            elsif(p3 = q3) then
                if(p2 > q2) then pout1 = '1'; pout3 = '0'; pout2 = '0';
                elsif(p2 < q2) then pout1 = '0'; pout3 = '1'; pout2 = '0';
                elsif(p2 = q2) then
                    if(p1 > q1) then pout1 = '1'; pout3 = '0'; pout2 = '0';
                    elsif(p1 < q1) then pout1 = '0'; pout3 = '1'; pout2 = '0';
                    elsif(p1 = q1) then
                        if(p0 > q0) then pout1 = '1'; pout3 = '0'; pout2 = '0';
                        elsif(p0 < q0) then pout1 = '0'; pout3 = '1'; pout2 = '0';
                        elsif(p0 = q0) then
                            if pqin3 = '1' and pqin1 ='0' and pqin2 = '0' then pout1 = '1'; pout3 = '0'; pout2 = '0';
                            elsif pqin3 = '0' and pqin1 ='1' and pqin2 = '0' then pout1 = '0'; pout3 = '1'; pout2 = '0';
                            elsif pqin3 = '0' and pqin1 ='0' and pqin2 = '1' then pout1 = '0'; pout3 = '0'; pout2 = '0';
                            elsif pqin3 = '0' and pqin1 ='0' and pqin2 = '0' then pout1 = '1'; pout3 = '1'; pout2 = '0';
                            else
                                pout1 = '0'; pout3 = '0'; pout2 = '0';
                            end if;
                        end if;
                    end if;
                end if;
            end if;
        end if;

    end process;



    P_QOUT1_5 <= pout1;
    P_QOUT2_6 <= pout2;
    P_QOUT3_7 <= pout3;


end MOD_74LS85_behv;

--- END_CODE ---
