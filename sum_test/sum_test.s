    org $0000
start
    clra
.loop
    inca
    cmpa 5
    beq halt
    bra .loop
halt
    nop
    bra halt

    org $FFFE
reset
    fcb $00 ; find mnemonic for storing word
    fcb $00
