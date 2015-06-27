----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    13:51:13 03/18/2015 
-- Design Name: 
-- Module Name:    sequential - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
library UNISIM;
use UNISIM.VComponents.all;

entity controller is
    Port ( POC : in  STD_LOGIC;
           SYSCLK : in  STD_LOGIC;
			  EF : IN std_logic_vector (4 downto 1);
			  ECOMP : IN STD_LOGIC;
			  GOIN_TO: out std_logic_vector (4 downto 1);
			  FLOOR_IND: out STD_LOGIC_vector (4 downto 1);
			  UP_REQ: in std_logic_vector (4 downto 1); -- 3-1 usable
			  DN_REQ: in std_logic_vector (4 downto 1); -- 4-2 usable
			  GO_REQ: in std_logic_vector (4 downto 1);
			  EMVUP: out STD_LOGIC;
			  EMVDN: out STD_LOGIC;
			  EOPEN: out STD_LOGIC;
			  ECLOSE: out STD_LOGIC);
			  --DI: out std_logic_vector(3 downto 1));
			  
end controller;

architecture Behavioral of controller is
	signal NEED_CLOSE: STD_LOGIC;
	signal SENT: STD_LOGIC;
	signal GOING_TO: std_logic_vector (4 downto 1); --(1st floor,2nd,3rd,4th)
	signal DIR: std_logic_vector(3 downto 1);--(1none,2up,3dn)
BEGIN
    process(SYSCLK)
        begin
            if (SYSCLK'event and SYSCLK='1') then  
						EOPEN<='0';
						ECLOSE<='0';
						EMVDN<='0';
						EMVUP<='0';
					if (POC='1') then  --floor=0 
						FLOOR_IND <= "0001";
						EMVUP<='0';
						EMVDN<='0';
						EOPEN<='0';
						ECLOSE<='0';
						SENT<='0';
						NEED_CLOSE<='0';
						GOING_TO<="0000";
						DIR<="001";
               elsif(ECOMP='1' AND SENT='0') then
					   EOPEN<='0';
						ECLOSE<='0';
						EMVDN<='0';
						EMVUP<='0';
						if(NEED_CLOSE='1') then --door is open and needs closed
							ECLOSE <='1';
							NEED_CLOSE<='0';
							SENT<='1';
						elsif(((GO_REQ AND EF) = EF) OR (EF=GOING_TO) OR (DIR(2)='1' AND ((UP_REQ AND EF)= EF)) OR (DIR(3)='1' AND (((DN_REQ AND EF)= EF) ))) then
							EOPEN <='1';
							NEED_CLOSE <='1';
							SENT<='1';
							if(GOING_TO=EF) then
								GOING_TO<="0000";
								DIR<="001";
							end if;
						elsif(GOING_TO/="0000" AND GOING_TO>EF) then
							EMVUP<='1';
							SENT<='1';
						elsif(GOING_TO/="0000" AND GOING_TO<EF) then
							EMVDN<='1';
							SENT<='1';
						elsif(DIR(1)='1') then--look for new place to go
							if(not(GO_REQ="0000")) then -- check inside buttons
								for i in 1 to 4 loop
									if(GO_REQ(i)='1') then 
										GOING_TO<="0000";
										GOING_TO(i)<='1';
									end if;
								end loop;
								DIR<="000";
								if(GOING_TO>EF) then --up
									DIR(2)<='1';
								elsif(GOING_TO<EF) then --down
									DIR(3)<='1';
								end if;
							elsif(not(UP_REQ="0000")) then --check up buttons
								for i in 1 to 4 loop
									if(UP_REQ(i)='1') then
										GOING_TO<="0000";
										GOING_TO(i)<='1';
										if(GOING_TO>EF) then --up
											DIR<="000";
											DIR(2)<='1';
										end if;
										--DIR(2)<='1';
									end if;
								end loop;
							elsif(not(DN_REQ="0000")) then --check dn buttons
								for i in 4 downto 1 loop
									if(DN_REQ(i)='1') then
										GOING_TO<="0000";
										GOING_TO(i)<='1';
										if(GOING_TO<EF) then --down
											DIR<="000";
											DIR(3)<='1';
										end if;
										--DIR(3)<='1';
									end if;
								end loop;
							end if;
						end if;
               elsif(ECOMP='0') then 
						EOPEN<='0';
						ECLOSE<='0';
						EMVDN<='0';
						EMVUP<='0';
						SENT<='0';
					end if; 
					FLOOR_IND<=EF;
					--DI<=DIR;
					GOIN_TO<=GOING_TO;
            end if;
    end process;
end Behavioral;


