Bestätigt ✅ · K501 · COMMUNICATION PROTOCOL REGISTRY · v0.1 🕊️💡

Mode: REFERENCE_ONLY · APPEND_ONLY

Scope: Verified Communication Protocols + Phantom Audit

Last Audit: 2026-02-23

  

  

  

  

Time Anchor

  

  

- Unix Epoch: 1771873734
- UTC: 2026-02-23T19:08:54Z
- Europe/Amsterdam: 2026-02-23T20:08:54 CET

  

  

  

  

────────────────────────────────────────────────────────

  

- name: HTTP  
    family: Web Transport  
    osi_layer: Application  
    transport: TCP  
    protocol_type: Request/Response  
    security_model: none (plaintext)  
    official_status: OFFICIAL  
    risk_flags:  
    

- no native encryption  
    urls:
- https://www.rfc-editor.org/rfc/rfc9110

-   
    

  

  

────────────────────────────────────────────────────────

  

- name: HTTPS  
    family: Web Transport  
    osi_layer: Application  
    transport: TCP + TLS  
    protocol_type: Request/Response  
    security_model: TLS encryption  
    official_status: OFFICIAL  
    risk_flags: none  
    urls:  
    

- https://www.rfc-editor.org/rfc/rfc9110
- https://www.rfc-editor.org/rfc/rfc8446

-   
    

  

  

────────────────────────────────────────────────────────

  

- name: FTP  
    family: File Transfer  
    osi_layer: Application  
    transport: TCP  
    protocol_type: Control + Data channels  
    security_model: none (plaintext)  
    official_status: OFFICIAL  
    risk_flags:  
    

- credentials in plaintext  
    urls:
- https://www.rfc-editor.org/rfc/rfc959

-   
    

  

  

────────────────────────────────────────────────────────

  

- name: SFTP  
    family: File Transfer  
    osi_layer: Application  
    transport: SSH  
    protocol_type: Secure file transfer  
    security_model: SSH encryption  
    official_status: OFFICIAL  
    risk_flags: none  
    urls:  
    

- https://www.rfc-editor.org/rfc/rfc4251

-   
    

  

  

────────────────────────────────────────────────────────

  

- name: SSH  
    family: Remote Access  
    osi_layer: Application  
    transport: TCP  
    protocol_type: Secure remote shell  
    security_model: encrypted channel  
    official_status: OFFICIAL  
    risk_flags: none  
    urls:  
    

- https://www.rfc-editor.org/rfc/rfc4251

-   
    

  

  

────────────────────────────────────────────────────────

  

- name: Telnet  
    family: Remote Access  
    osi_layer: Application  
    transport: TCP  
    protocol_type: Terminal session  
    security_model: none (plaintext)  
    official_status: OFFICIAL  
    risk_flags:  
    

- insecure legacy protocol  
    urls:
- https://www.rfc-editor.org/rfc/rfc854

-   
    

  

  

────────────────────────────────────────────────────────

  

- name: SMTP  
    family: Email  
    osi_layer: Application  
    transport: TCP  
    protocol_type: Mail transfer  
    security_model: optional STARTTLS  
    official_status: OFFICIAL  
    risk_flags:  
    

- plaintext possible  
    urls:
- https://www.rfc-editor.org/rfc/rfc5321

-   
    

  

  

────────────────────────────────────────────────────────

  

- name: IMAP  
    family: Email  
    osi_layer: Application  
    transport: TCP  
    protocol_type: Mail retrieval  
    security_model: optional TLS  
    official_status: OFFICIAL  
    risk_flags: none  
    urls:  
    

- https://www.rfc-editor.org/rfc/rfc9051

-   
    

  

  

────────────────────────────────────────────────────────

  

- name: POP3  
    family: Email  
    osi_layer: Application  
    transport: TCP  
    protocol_type: Mail retrieval  
    security_model: optional TLS  
    official_status: OFFICIAL  
    risk_flags: none  
    urls:  
    

- https://www.rfc-editor.org/rfc/rfc1939

-   
    

  

  

────────────────────────────────────────────────────────

  

- name: NTP  
    family: Time Synchronization  
    osi_layer: Application  
    transport: UDP  
    protocol_type: Time sync  
    security_model: limited (NTS optional)  
    official_status: OFFICIAL  
    risk_flags:  
    

- spoofing risk without NTS  
    urls:
- https://www.rfc-editor.org/rfc/rfc5905

-   
    

  

  

────────────────────────────────────────────────────────

  

- name: RSS  
    family: Web Syndication  
    osi_layer: Application  
    transport: HTTP/HTTPS  
    protocol_type: XML feed  
    security_model: transport-dependent  
    official_status: OFFICIAL  
    risk_flags: none  
    urls:  
    

- https://www.rssboard.org/rss-specification

-   
    

  

  

────────────────────────────────────────────────────────

  

- name: Atom  
    family: Web Syndication  
    osi_layer: Application  
    transport: HTTP/HTTPS  
    protocol_type: XML feed  
    security_model: transport-dependent  
    official_status: OFFICIAL  
    risk_flags: none  
    urls:  
    

- https://www.rfc-editor.org/rfc/rfc4287

-   
    

  

  

────────────────────────────────────────────────────────

  

- name: Wi-Fi (IEEE 802.11)  
    family: Wireless LAN  
    osi_layer: Physical + Data Link  
    transport: RF (2.4/5/6 GHz)  
    protocol_type: MAC/PHY  
    security_model: WPA2/WPA3  
    official_status: OFFICIAL  
    risk_flags:  
    

- depends on configuration  
    urls:
- https://standards.ieee.org/ieee/802.11

-   
    

  

  

────────────────────────────────────────────────────────

  

- name: Bluetooth (Classic + BLE)  
    family: Wireless PAN  
    osi_layer: Physical + Data Link  
    transport: RF 2.4 GHz  
    protocol_type: PAN stack  
    security_model: pairing + encryption  
    official_status: OFFICIAL  
    risk_flags:  
    

- pairing vulnerabilities possible  
    urls:
- https://www.bluetooth.com/specifications/

-   
    

  

  

────────────────────────────────────────────────────────

  

- name: NFC  
    family: Short-Range Wireless  
    osi_layer: Physical + Data Link  
    transport: RF (13.56 MHz)  
    protocol_type: proximity communication  
    security_model: short-range + optional crypto  
    official_status: OFFICIAL  
    risk_flags:  
    

- relay attacks possible  
    urls:
- https://www.iso.org/standard/73566.html

-   
    

  

  

────────────────────────────────────────────────────────

  

- name: USB  
    family: Wired Bus  
    osi_layer: Physical + Data Link  
    transport: wired differential  
    protocol_type: host-device bus  
    security_model: none inherent  
    official_status: OFFICIAL  
    risk_flags:  
    

- BadUSB class attacks  
    urls:
- https://usb.org/document-library

-   
    

  

  

────────────────────────────────────────────────────────

  

- name: Micro-USB  
    family: Connector Standard  
    osi_layer: Physical  
    transport: USB physical  
    protocol_type: connector (not protocol)  
    security_model: inherits USB  
    official_status: OFFICIAL_LIMITED  
    risk_flags:  
    

- not a communication protocol  
    urls:
- https://usb.org

-   
    

  

  

────────────────────────────────────────────────────────

  

END OF REGISTRY

Status: CANONICAL BASELINE · PHANTOM AUDIT PASS 🥇🕊️💡