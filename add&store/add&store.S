.org $8000
    LDA     #$5
    ADDA    #$5
    STA     result
    
rpt:
    jmp rpt
    
result: fcb 0

.org $FFFE
    fcb $80
    fcb $00
