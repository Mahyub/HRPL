<?xml version="1.0" encoding="UTF-8"?>
<simconf>
  <project EXPORT="discard">[APPS_DIR]/mrm</project>
  <project EXPORT="discard">[APPS_DIR]/mspsim</project>
  <project EXPORT="discard">[APPS_DIR]/avrora</project>
  <project EXPORT="discard">[APPS_DIR]/serial_socket</project>
  <project EXPORT="discard">[APPS_DIR]/collect-view</project>
  <project EXPORT="discard">[APPS_DIR]/powertracker</project>
  <simulation>
    <title>p2p-grid-large-4-sim</title>
    <randomseed>generated</randomseed>
    <motedelay_us>1000000</motedelay_us>
    <radiomedium>
      org.contikios.cooja.radiomediums.UDGM
      <transmitting_range>90.0</transmitting_range>
      <interference_range>120.0</interference_range>
      <success_ratio_tx>1.0</success_ratio_tx>
      <success_ratio_rx>1.0</success_ratio_rx>
    </radiomedium>
    <events>
      <logoutput>40000</logoutput>
    </events>
    <motetype>
      org.contikios.cooja.mspmote.WismoteMoteType
      <identifier>wismote1</identifier>
      <description>Wismote Root</description>
      <source EXPORT="discard">[CONFIG_DIR]/../app-p2p-sim-root.c</source>
      <commands EXPORT="discard">make app-p2p-sim-root.wismote TARGET=wismote</commands>
      <firmware EXPORT="copy">[CONFIG_DIR]/../app-p2p-sim-root.wismote</firmware>
      <moteinterface>org.contikios.cooja.interfaces.Position</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.RimeAddress</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.IPAddress</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.Mote2MoteRelations</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.MoteAttributes</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspClock</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspMoteID</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspButton</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.Msp802154Radio</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspDefaultSerial</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspLED</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspDebugOutput</moteinterface>
    </motetype>
    <motetype>
      org.contikios.cooja.mspmote.WismoteMoteType
      <identifier>wismote2</identifier>
      <description>Wismote Node</description>
      <source EXPORT="discard">[CONFIG_DIR]/../app-p2p-sim-node.c</source>
      <commands EXPORT="discard">make app-p2p-sim-node.wismote TARGET=wismote</commands>
      <firmware EXPORT="copy">[CONFIG_DIR]/../app-p2p-sim-node.wismote</firmware>
      <moteinterface>org.contikios.cooja.interfaces.Position</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.RimeAddress</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.IPAddress</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.Mote2MoteRelations</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.MoteAttributes</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspClock</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspMoteID</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspButton</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.Msp802154Radio</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspDefaultSerial</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspLED</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspDebugOutput</moteinterface>
    </motetype>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>0.0</x>
        <y>50.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>2</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>0.0</x>
        <y>100.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>3</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>0.0</x>
        <y>150.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>4</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>0.0</x>
        <y>200.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>5</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>50.0</x>
        <y>0.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>6</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>50.0</x>
        <y>50.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>7</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>50.0</x>
        <y>100.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>8</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>50.0</x>
        <y>150.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>9</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>50.0</x>
        <y>200.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>10</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>100.0</x>
        <y>0.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>11</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>100.0</x>
        <y>50.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>12</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>100.0</x>
        <y>100.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>13</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>100.0</x>
        <y>150.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>14</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>100.0</x>
        <y>200.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>15</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>150.0</x>
        <y>0.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>16</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>150.0</x>
        <y>50.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>17</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>150.0</x>
        <y>100.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>18</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>150.0</x>
        <y>150.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>19</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>150.0</x>
        <y>200.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>20</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>200.0</x>
        <y>0.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>21</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>200.0</x>
        <y>50.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>22</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>200.0</x>
        <y>100.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>23</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>200.0</x>
        <y>150.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>24</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>200.0</x>
        <y>200.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>25</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>250.0</x>
        <y>0.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>26</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>250.0</x>
        <y>50.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>27</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>250.0</x>
        <y>100.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>28</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>250.0</x>
        <y>150.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>29</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>250.0</x>
        <y>200.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>30</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>300.0</x>
        <y>0.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>31</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>300.0</x>
        <y>50.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>32</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>300.0</x>
        <y>100.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>33</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>300.0</x>
        <y>150.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>34</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>300.0</x>
        <y>200.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>35</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>350.0</x>
        <y>0.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>36</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>350.0</x>
        <y>50.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>37</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>350.0</x>
        <y>100.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>38</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>350.0</x>
        <y>150.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>39</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>350.0</x>
        <y>200.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>40</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>400.0</x>
        <y>0.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>41</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>400.0</x>
        <y>50.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>42</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>400.0</x>
        <y>100.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>43</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>400.0</x>
        <y>150.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>44</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>400.0</x>
        <y>200.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>45</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>450.0</x>
        <y>0.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>46</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>450.0</x>
        <y>50.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>47</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>450.0</x>
        <y>100.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>48</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>450.0</x>
        <y>150.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>49</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>450.0</x>
        <y>200.0</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>50</id>
      </interface_config>
      <motetype_identifier>wismote2</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>24.38508829129039</x>
        <y>24.62597793666119</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspClock
        <deviation>1.0</deviation>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>1</id>
      </interface_config>
      <motetype_identifier>wismote1</motetype_identifier>
    </mote>
  </simulation>
  <plugin>
    org.contikios.cooja.plugins.SimControl
    <width>262</width>
    <z>0</z>
    <height>160</height>
    <location_x>96</location_x>
    <location_y>796</location_y>
  </plugin>
  <plugin>
    org.contikios.cooja.plugins.ScriptRunner
    <plugin_config>
      <script>load("nashorn:mozilla_compat.js");
importPackage(java.io);

TIMEOUT(21000000);
nrNodes = 50;
path_len = 30;
total_reports = 0;
total_reports_needed = nrNodes;
all_reported = false;
TIME_OUT_FINALIZE = 20000000;

/* configuration at start */
/*----power statstics arrays ------*/
cpu = new Array();	lpm = new Array();	rx = new Array();	tx = new Array();
all_cpu = 0;	all_lpm = 0;	all_rx = 0;	all_tx = 0;	all_energy = 0;

/* app layer */
app_sent = new Array();	app_recv = new Array();	
all_app_sent = 0;	all_app_recv = 0;	all_PDR = 0;

/* RPL control messages */
dio_sent = new Array();	dao_sent = new Array();	dis_sent = new Array();	
all_dio_sent = 0;	all_dao_sent = 0;	all_dis_sent = 0;	all_rpl_msgs = 0;   

/*rpl statistics*/
rpl_mem_overf  = new Array();	rpl_loc_rep   = new Array();	rpl_glo_rep   = new Array();
rpl_malf_msgs = new Array();	rpl_resets    = new Array();	rpl_par_switch= new Array();
rpl_for_er    = new Array();	rpl_loop_er   = new Array();	rpl_loop_warn = new Array();
rpl_root_rep  = new Array();	

all_rpl_mem_overf = 0;			all_rpl_loc_rep   = 0;			all_rpl_glo_rep   = 0;
all_rpl_malf_msgs = 0;			all_rpl_resets    = 0;			all_rpl_par_switch= 0;
all_rpl_for_er    = 0;			all_rpl_loop_er   = 0;			all_rpl_loop_warn = 0;
all_rpl_root_rep  = 0;	 

/*---- mac layer -----*/
buf_drop = new Array();			routing_drop = new Array();		mac_drop = new Array(); 
rpl_mem_over  = new Array();	sugg_etx = new Array();		    actual_etx = new Array();
all_buf_drop = 0;				all_routing_drop = 0;			all_mac_drop = 0;	
all_rpl_mem_over=0; 			all_sugg_etx = 0; 				all_actual_etx = 0; 

/*hops and path cost*/
hops = new Array(); //number of hops array (cell per node) per received packet
hopsCDF = new Array(); //histogram for each hop variable(cell per each hop value)
all_hops_recv =0; //number of hops for all received packets only
all_hops_all=0; //number of hops for all received and dropped packets

node_reported = new Array();

output0 = new Object();
output1 = new Object();	output2 = new Object();	output3 = new Object();
output4 = new Object();	output5 = new Object();	output6 = new Object();
output7 = new Object();	output8 = new Object();	

AllRowDataDescfile  = "1row_data_all.dat"; 
AllEnergyDescfile   = "1energy_all.dat";	  IndEnergyDescfile  = "1energy_ind.dat";
AllPacketDescfile   = "1packet_all.dat";	  IndPacketDescfile  = "1packet_ind.dat";
AllAppOutputDescfile= "1app_output_all.dat";  AllhopsCDFDesfile  = "1hopsCDF.dat";
AllRplStatsDescfile = "1rpl_stats_all.dat";   IndRplStatsDescfile= "1rpl_stats_ind.dat"; 

for (i = 1; i &lt;= nrNodes; i++) {
	node_reported[i] = false;
	cpu[i] = 0;				lpm[i] = 0;	rx[i]  = 0;	tx[i]  = 0;
	app_sent[i] = 0;		app_recv[i] = 0;		hops[i]     = 0;
	dio_sent[i] = 0;		dao_sent[i] = 0;		dis_sent[i] = 0;  
	buf_drop[i] = 0;		routing_drop[i] = 0;	mac_drop[i] = 0; 
	rpl_mem_over [i] = 0;   sugg_etx [i]=0;			actual_etx [i]=0;
	
	rpl_mem_overf[i]= 0;	rpl_loc_rep[i]= 0;		rpl_glo_rep[i]   = 0;			
	rpl_malf_msgs[i]= 0;	rpl_resets[i] = 0;		rpl_par_switch[i]= 0;
	rpl_for_er[i]   = 0;	rpl_loop_er[i]= 0;		rpl_loop_warn[i] = 0;		
	rpl_root_rep[i] = 0;		
}
for (i = 0; i &lt;= path_len; i++){hopsCDF[i]=0;}

/* This loop will run till the end and wait for different messages to record them */
while (true) {
	// create different log files
	if (!output0[AllRowDataDescfile]) {
		output0[AllRowDataDescfile] = new FileWriter(AllRowDataDescfile);
		slinetowrite = "#id  @ time(ms)          message" + "\n";
		output0[AllRowDataDescfile].write(slinetowrite);
	}
	if (!output1[AllEnergyDescfile]) {
		output1[AllEnergyDescfile] = new FileWriter(AllEnergyDescfile);
		slinetowrite = "#Time:     total      cpu     lpm       rx       tx"    + "\n";
		output1[AllEnergyDescfile].write(slinetowrite);
	}
	if (!output2[IndEnergyDescfile]) {
		output2[IndEnergyDescfile] = new FileWriter(IndEnergyDescfile);
		slinetowrite = "#Time:   id     total      cpu     lpm       rx       tx"    + "\n";
		output2[IndEnergyDescfile].write(slinetowrite);
	}
	if (!output3[AllPacketDescfile]) {
		output3[AllPacketDescfile] = new FileWriter(AllPacketDescfile);
		slinetowrite = "#Time:  app_s   app_r   PDR    rpl_msgs   dio_s   dao_s   dis_s   mem_over   rout_d   buf_d   mac_d  hops_recv hops_all   sugg_etx  mac_tx"+ "\n";
		output3[AllPacketDescfile].write(slinetowrite);
	}
	if (!output4[IndPacketDescfile]) {
		output4[IndPacketDescfile] = new FileWriter(IndPacketDescfile);
		slinetowrite = "#Time:    id:  app_s	   app_r	 dio_s	   dao_s	dis_s	 mem_over    route_d    buf_d   mac_d    actual_etx"+ "\n";
		output4[IndPacketDescfile].write(slinetowrite);
	}
	if (!output5[AllAppOutputDescfile]) {
		output5[AllAppOutputDescfile] = new FileWriter(AllAppOutputDescfile);
		slinetowrite = "#node_id at time(ms) : message "+ "\n";
		output5[AllAppOutputDescfile].write(slinetowrite);
	}
	if (!output6[AllhopsCDFDesfile]) {
		output6[AllhopsCDFDesfile] = new FileWriter(AllhopsCDFDesfile);
		slinetowrite = "#The frequency of the hop variable in scale of 0 to "+ path_len + "\n";
		output6[AllhopsCDFDesfile].write(slinetowrite);
	}
	if (!output7[AllRplStatsDescfile]) {
		output7[AllRplStatsDescfile] = new FileWriter(AllRplStatsDescfile);
		slinetowrite = "#Time:   dia   dao   dis   m_over    loc_rep   glo_rep   malfs   reset   par_sw   for_err   loop_err   loop_wrn   root_rep" + "\n";
		output7[AllRplStatsDescfile].write(slinetowrite);
	}
	if (!output8[IndRplStatsDescfile]) {
		output8[IndRplStatsDescfile] = new FileWriter(IndRplStatsDescfile);
		slinetowrite = "#Time:    id   dia   dao   dis   m_over  loc_rep   glo_rep   malfs   reset   par_sw   for_err   loop_err   loop_wrn   root_rep" + "\n";
		output8[IndRplStatsDescfile].write(slinetowrite);
	}
	try {
		YIELD();
	} catch (e) {
		output0[AllRowDataDescfile].close();	
		output1[AllEnergyDescfile].close();		output2[IndEnergyDescfile].close();
		output3[AllPacketDescfile].close();		output4[IndPacketDescfile].close();
		output5[AllAppOutputDescfile].close();	output6[AllhopsCDFDesfile].close();
		output7[AllRplStatsDescfile].close();	output8[IndRplStatsDescfile].close();
		throw ('test script killed');
	}
	
	slinetowrite = id + "  " + sim.getSimulationTimeMillis() + "   " + msg + "\n";
	output0[AllRowDataDescfile].write(slinetowrite);
	// Recording Statistics message
	if ((!msg.contains("app_send:")) 			 &amp;&amp; (!msg.contains("app_recv:"))
			&amp;&amp; (!msg.contains("energy:")) 
			&amp;&amp; (!msg.contains("routing_drop:"))  &amp;&amp; (!msg.contains("rpl_dio:"))
			&amp;&amp; (!msg.contains("rpl_dao:")) 	     &amp;&amp; (!msg.contains("rpl_dis:")) 
			&amp;&amp; (!msg.contains("rpl_mem_over:"))  &amp;&amp; (!msg.contains("bufferflow_drop:"))	
			&amp;&amp; (!msg.contains("mac_drop:")) 	 &amp;&amp; (!msg.contains("mac_num_tx:"))  
			&amp;&amp; (!msg.contains("new_hop:")) 		 &amp;&amp; (!msg.contains("rpl_stats:"))
			&amp;&amp; (!msg.contains("hrreq_send:")) 	 &amp;&amp; (!msg.contains("hrreq_recv:")) 
			&amp;&amp; (!msg.contains("hrrep_send:")) 	 &amp;&amp; (!msg.contains("hrrep_recv:")) 
			&amp;&amp; (!msg.contains("timeout_timer:")) &amp;&amp; (!msg.contains("hrrer_send:"))) 
	{continue};

	if (msg.startsWith("app_recv:")) {
		slinetowrite = id + " at " + sim.getSimulationTimeMillis() + " : " + msg + "\n";
		output5[AllAppOutputDescfile].write(slinetowrite);
		// Received packet
		app_recv[id]++;
		data = msg.split(" ");
		hops[id]+= Number(data[4]); //parseInt(data[4])
		hopsCDF[Number(data[4])]++;
		sugg_etx[id]+= Number(data[6]);
		actual_etx[id]+= Number(data[8]);
	}
	if (msg.startsWith("app_send:")) {
		slinetowrite = id + " at " + sim.getSimulationTimeMillis() + " : " + msg + "\n";
		output5[AllAppOutputDescfile].write(slinetowrite);
		app_sent[id]++;
	}
	if (msg.startsWith("hrreq_send:")) {
		slinetowrite = id + " at " + sim.getSimulationTimeMillis() + " : " + msg + "\n";
		output5[AllAppOutputDescfile].write(slinetowrite);
	}
	if (msg.startsWith("hrreq_recv:")) {
		slinetowrite = id + " at " + sim.getSimulationTimeMillis() + " : " + msg + "\n";
		output5[AllAppOutputDescfile].write(slinetowrite);
	}
	if (msg.startsWith("hrrep_send:")) {
		slinetowrite = id + " at " + sim.getSimulationTimeMillis() + " : " + msg + "\n";
		output5[AllAppOutputDescfile].write(slinetowrite);
	}
	if (msg.startsWith("hrrep_recv:")) {
		slinetowrite = id + " at " + sim.getSimulationTimeMillis() + " : " + msg + "\n";
		output5[AllAppOutputDescfile].write(slinetowrite);
	}
	if (msg.startsWith("timeout_timer:")) {
		slinetowrite = id + " at " + sim.getSimulationTimeMillis() + " : " + msg + "\n";
		output5[AllAppOutputDescfile].write(slinetowrite);
	}
	if (msg.startsWith("hrrer_send:")) {
		slinetowrite = id + " at " + sim.getSimulationTimeMillis() + " : " + msg + "\n";
		output5[AllAppOutputDescfile].write(slinetowrite);
	}
	if (msg.startsWith("energy:")) {
		data = msg.split("  ");
		cpu[id] = Number(data[1]);				lpm[id] = Number(data[2]);
		rx[id]  = Number(data[3]);				tx[id]  = Number(data[4]);
	}
	if (msg.startsWith("rpl_mem_over:")) {
		rpl_mem_over[id]++;
	}
	if (msg.startsWith("rpl_stats:")) {
		data = msg.split("  ");
		rpl_mem_over[id] = Number(data[1]);		rpl_loc_rep[id]   = Number(data[2]);
		rpl_glo_rep[id]  = Number(data[3]);		rpl_malf_msgs[id] = Number(data[4]);
		rpl_resets[id]   = Number(data[5]);		rpl_par_switch[id]=Number(data[6]);
		rpl_for_er[id]   = Number(data[7]);		rpl_loop_er[id]   = Number(data[8]);
		rpl_loop_warn[id]= Number(data[9]);		rpl_root_rep[id]  = Number(data[10]);
	}
	if (msg.startsWith("routing_drop:")) {
		routing_drop[id]++;
	}
	if (msg.startsWith("rpl_dio:")) {
		dio_sent[id]++;
	}
	if (msg.startsWith("rpl_dao:")) {
		dao_sent[id]++;
	}
	if (msg.startsWith("rpl_dis:")) {
		dis_sent[id]++;
	}
	if (msg.startsWith("bufferflow_drop:")) {
		buf_drop[id]++;
	}
	if (msg.startsWith("mac_drop:")) {
		mac_drop[id]++;
	}
	if (msg.startsWith("mac_num_tx:")) {
		slinetowrite = id + " at " + sim.getSimulationTimeMillis() + " : " + msg + "\n";
		output5[AllAppOutputDescfile].write(slinetowrite);
	}
	if (msg.startsWith("new_hop:")) {
		all_hops_all++;
	}
	if ((node_reported[id] == false) &amp;&amp; (cpu[id] != 0)) {
		node_reported[id] = true;
		total_reports++;
	}
	/* Recording details till and rest after each time window */
	if (total_reports &gt;= total_reports_needed) {
		all_reported = true;
	}
	if (all_reported) {
		all_reported = false;
		for (i = 2; i &lt;= nrNodes; i++) {
			cpu[i] = (cpu[i] *  2.2 * 3)/ 32768;
			lpm[i] = (lpm[i]*0.00169* 3)/ 32768;
			rx[i]  = (rx[i]  *  18.5* 3)/ 32768;
			tx[i]  = (tx[i]  *  25.8* 3)/ 32768;			
			all_cpu += cpu[i];	all_lpm += lpm[i];	
			all_rx  += rx[i];	all_tx  += tx[i];
		}
		for (i = 1; i &lt;= nrNodes; i++) {
			all_app_sent += app_sent[i];			all_app_recv += app_recv[i];
			all_dio_sent += dio_sent[i];   			all_dao_sent += dao_sent[i];	
			all_dis_sent += dis_sent[i];
			all_rpl_mem_over += rpl_mem_over [i];	all_routing_drop += routing_drop[i];	
			all_mac_drop += mac_drop[i];			all_buf_drop += buf_drop[i];
			all_sugg_etx += sugg_etx[i];			all_actual_etx += actual_etx [i];	
			all_hops_recv     += hops[i];  
			all_rpl_mem_overf += rpl_mem_overf[i];	all_rpl_loc_rep   += rpl_loc_rep[i];	
			all_rpl_glo_rep   += rpl_glo_rep[i];	all_rpl_malf_msgs += rpl_malf_msgs[i];	
			all_rpl_resets    += rpl_resets[i];		all_rpl_par_switch+= rpl_par_switch[i];
			all_rpl_for_er    += rpl_for_er[i];		all_rpl_loop_er   += rpl_loop_er[i];	
			all_rpl_loop_warn += rpl_loop_warn[i];	all_rpl_root_rep  += rpl_root_rep[i];	
		}
		all_energy = all_cpu + all_lpm + all_rx + all_tx ;
		all_rpl_msgs = all_dio_sent + all_dao_sent + all_dis_sent;	
		all_PDR = all_app_recv / all_app_sent;
		
		if (sim.getSimulationTimeMillis() &gt; TIME_OUT_FINALIZE) {
			print_individual_stats_end();
			print_all_stats_periodic();
			log.log("================================ Ended at " + gtime + "======================\n");
			output0[AllRowDataDescfile].close();	
			output1[AllEnergyDescfile].close();			output2[IndEnergyDescfile].close();
			output3[AllPacketDescfile].close();			output4[IndPacketDescfile].close();
			output5[AllAppOutputDescfile].close();		output6[AllhopsCDFDesfile].close();
			output7[AllRplStatsDescfile].close();		output8[IndRplStatsDescfile].close();
			SCRIPT_TIMEOUT();
		}else{
			print_all_stats_periodic();
			
			all_PDR 	 =0;	    all_app_recv 	=0; 	all_app_sent     =0; 	all_hops_recv =0;
			all_rpl_msgs =0;	    all_dio_sent 	=0;		all_dao_sent     =0;    all_dis_sent =0;
			all_buf_drop =0;        all_routing_drop =0;  	all_rpl_mem_over =0; 	all_mac_drop =0;  
			all_sugg_etx=0;		    all_actual_etx 	= 0; 
			all_rpl_mem_overf = 0;	all_rpl_loc_rep = 0;	all_rpl_glo_rep   = 0;		
			all_rpl_malf_msgs = 0;	all_rpl_resets  = 0;	all_rpl_par_switch= 0;
			all_rpl_for_er    = 0;	all_rpl_loop_er = 0;	all_rpl_loop_warn = 0;		
			all_rpl_root_rep  = 0;	
			all_cpu	     =0;	  	all_lpm =0;all_rx =0;	all_tx =0;	all_energy =0;
			total_reports=0;
			
			for (i = 1; i &lt;= nrNodes; i++) {
				node_reported[i] = false;
				rpl_mem_overf[i]= 0;	    rpl_loc_rep[i]= 0;		rpl_glo_rep[i]   = 0;			
				rpl_malf_msgs[i]= 0;		rpl_resets[i] = 0;		rpl_par_switch[i]= 0;
				rpl_for_er[i]   = 0;		rpl_loop_er[i]= 0;		rpl_loop_warn[i] = 0;		
				rpl_root_rep[i] = 0;
				cpu[i]= 0;					lpm[i]= 0;rx[i]= 0;		tx[i]= 0;
			}
		}
	}
}

function print_individual_stats_end(){
	/* Time is rounded */
	gtime = time / 1000000;
	remainder = gtime % 60;
	if (remainder &lt; 20) {
		gtime = gtime - remainder;
	}
	//File to save aggregated power per-individual statistics: IndEnergyDescfile
	log.log("IndEnergyDescfile : \n");
	slinetowrite = "#T: id     total      cpu     lpm       rx       tx"    + "\n";
	log.log(slinetowrite);
	for (i = 2; i &lt;= nrNodes; i++) {
	writeinfile = Math.round(gtime, 1) + "   " + i  
	+ "   "	+ (cpu[i] + lpm[i]  + tx[i] + rx[i]).toFixed(3)  
	+ "   " + cpu[i].toFixed(3) + "   "	+ lpm[i].toFixed(3) 
	+ "   " + rx[i].toFixed(3)  + "   "	+ tx[i].toFixed(3) + "\n";
	output2[IndEnergyDescfile].write(writeinfile);
	log.log(writeinfile);
	}
	log.log("===================================================================================\n");
	
	// File to save aggregated packets per-individuls statistics:  IndPacketDescfile.
	log.log("IndPacketDescfile : \n");
	slinetowrite = "#T: id:  app_s app_r   dio_s  dao_s  dis_s mem_over route_d buf_d  mac_d  actual_etx"
		+ "\n";
	log.log(slinetowrite);
	for (i = 1; i &lt;= nrNodes; i++) {
	writeinfile = Math.round(gtime, 1) + "   " + i 
	+ "   " + app_sent[i]      + "   " + app_recv[i] 
	+ "   " + dio_sent[i]      + "   " + dao_sent[i]     + "   " + dis_sent[i]
	+ "   " + rpl_mem_over[i]  + "   " +routing_drop[i]  + "   " + buf_drop[i]
	+ "   " + mac_drop[i]      + "   " + actual_etx[i] + "\n" ;
	output4[IndPacketDescfile].write(writeinfile);
	log.log(writeinfile);
	}
	log.log("===================================================================================\n");
	
	// File to save aggregated rpl states per-individuls statistics:  IndRplStatsDescfile.
	log.log("IndRplStatsDescfile : \n");
	slinetowrite = "#T:    id   dia   dao   dis   m_over  loc_rep   glo_rep   malfs   reset   par_sw   for_err   loop_err   loop_wrn   root_rep" + "\n";
	log.log(slinetowrite);
	for (i = 1; i &lt;= nrNodes; i++) {
	writeinfile = Math.round(gtime, 1) + "   " + i 
	+ "   " + dio_sent[i]       + "   " + dao_sent[i]    + "   " + dis_sent[i]
	+ "   " + rpl_mem_overf[i]	+ "   " + rpl_loc_rep[i] + "   " + rpl_glo_rep[i]
	+ "   " + rpl_malf_msgs[i]  + "   " + rpl_resets[i]  + "   " + rpl_par_switch[i]
	+ "   " + rpl_for_er[i]     + "   " + rpl_loop_er[i] + "   " + rpl_loop_warn[i]
	+ "   " + rpl_root_rep[i]   +"\n" ;
	output8[IndRplStatsDescfile].write(writeinfile);
	log.log(writeinfile);
	}
	log.log("===================================================================================\n");
}

function print_all_stats_periodic() {
	/* Time is rounded */
	gtime = time / 1000000;
	remainder = gtime % 60;
	if (remainder &lt; 20) {
		gtime = gtime - remainder;
	}	
	
	// File to save aggregated energy statistics: AllEnergyDescfile
	log.log("AllEnergyDescfile: \n");
	slinetowrite = "#T:        all_energy      all_cpu      all_lpm        all_rx         all_tx"
		+ "\n";
	log.log(slinetowrite);
	writeinfile = Math.round(gtime, 1) 
	+ "     " + all_energy.toFixed(2) 
	+ "     " + all_cpu.toFixed(2) + "     " + all_lpm.toFixed(2) 
	+ "     " + all_rx.toFixed(2)  + "     " + all_tx.toFixed(2) + "\n";
	output1[AllEnergyDescfile].write(writeinfile);
	log.log(writeinfile);
	log.log("===================================================================================\n");
	
	// File to save aggregated packets statistics: AllPacketDesfile
	log.log("AllPacketDescfile : \n");
	slinetowrite = "#T:  app_s   app_r   PDR   rpl_msgs   dio_s   dao_s   dis_s   mem_over rout_d   buf_d   mac_d  hops_recv hops_all  sugg_etx   mac_tx"
		+ "\n";
	log.log(slinetowrite);
	writeinfile = Math.round(gtime, 1) 
	+ "   " + all_app_sent   	+ "   " + all_app_recv 		+ "   " + all_PDR.toFixed(3) 
	+ "   " + all_rpl_msgs   	+ "   " + all_dio_sent 		+ "   " + all_dao_sent 
	+ "   "	+ all_dis_sent		+ "   " + all_rpl_mem_over  + "   " + all_routing_drop 
	+ "   " + all_buf_drop 		+ "   " + all_mac_drop      + "   " + all_hops_recv      
	+ "   " + all_hops_all		+ "   " + all_sugg_etx 		+ "   " + all_actual_etx + "\n";
	log.log(writeinfile);
	output3[AllPacketDescfile].write(writeinfile);
	log.log("===================================================================================\n");

	// File to save the aggregated hop variable frequency for hops-CDF
	log.log("AllhopsCDFDesfile : \n");
	output6[AllhopsCDFDesfile].write(Math.round(gtime, 1)+"   ");
	for (i = 0; i &lt;= path_len; i++) {
		slinetowrite = hopsCDF[i] + "   " ;
		output6[AllhopsCDFDesfile].write(slinetowrite);
		log.log(slinetowrite);
		}
	output6[AllhopsCDFDesfile].write("\n");
	log.log("\n");
	log.log("===================================================================================\n");

	// File to save aggregated rpl statistics: AllRplStatsDescfile
	log.log("AllRplStatsDescfile : \n");
	slinetowrite = "#T:   dia   dao   dis   m_over    loc_rep   glo_rep   malfs   reset   par_sw   for_err   loop_err   loop_wrn   root_rep" + "\n";
	log.log(slinetowrite);
	writeinfile = Math.round(gtime, 1) 
	+ "   " + all_rpl_msgs   	 + "   " + all_dio_sent       + "   " + all_dao_sent    
	+ "   " + all_dis_sent 		 + "   " + all_rpl_mem_overf  + "   " + all_rpl_loc_rep    
	+ "   " + all_rpl_glo_rep 	 + "   " + all_rpl_malf_msgs  + "   " + all_rpl_resets     
	+ "   " + all_rpl_par_switch + "   " + all_rpl_for_er  	  + "   " + all_rpl_loop_er 
	+ "   " + all_rpl_loop_warn  + "   " + all_rpl_root_rep	  + "\n";
	log.log(writeinfile);
	output7[AllRplStatsDescfile].write(writeinfile);
log.log("*********************************************************************************\n");
}</script>
      <active>true</active>
    </plugin_config>
    <width>715</width>
    <z>2</z>
    <height>954</height>
    <location_x>559</location_x>
    <location_y>3</location_y>
  </plugin>
  <plugin>
    org.contikios.cooja.plugins.Visualizer
    <plugin_config>
      <moterelations>true</moterelations>
      <skin>org.contikios.cooja.plugins.skins.IDVisualizerSkin</skin>
      <skin>org.contikios.cooja.plugins.skins.UDGMVisualizerSkin</skin>
      <skin>org.contikios.cooja.plugins.skins.MoteTypeVisualizerSkin</skin>
      <viewport>0.9619834710743801 0.0 0.0 0.9619834710743801 16.793459034792473 13.48033807774715</viewport>
    </plugin_config>
    <width>510</width>
    <z>3</z>
    <height>284</height>
    <location_x>3</location_x>
    <location_y>510</location_y>
  </plugin>
  <plugin>
    org.contikios.cooja.plugins.LogListener
    <plugin_config>
      <filter />
      <formatted_time />
      <coloring />
    </plugin_config>
    <width>552</width>
    <z>1</z>
    <height>501</height>
    <location_x>3</location_x>
    <location_y>7</location_y>
  </plugin>
</simconf>

