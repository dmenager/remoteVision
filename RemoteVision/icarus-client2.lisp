;******************************************************************************
;******************************************************************************
; ICARUS-CLIENT.LISP
;
; This file implement a TCP Client in CLISP 
;******************************************************************************
;******************************************************************************

(defpackage "ICARUS-CLIENT" (:use "COMMON-LISP" "SOCKET"))

(setf SERVER_IP "127.0.0.1")
(setf SERVER_PORT 6000)

(DEFUN socketClient (host port message)
    ; Open connection
	; Change this to a specific OS on server/client EXTERNAL-FORMAT :UNIX / :DOS
    (WITH-OPEN-STREAM (socket (SOCKET:SOCKET-CONNECT port host :EXTERNAL-FORMAT :UNIX))
        (SETF i 0)
        ; Verify if the connection is ok
        (LOOP 
            (WHEN (EQ :eof (SOCKET:SOCKET-STATUS (cons socket :output))) (RETURN))
                ; Send data             
                (WRITE-LINE message socket)
                (force-output socket)

                ; Receive data
                (SETF input "")
                (IF (EQ :eof (SOCKET:SOCKET-STATUS (cons socket :input))) (RETURN))
                (SETF input (READ-LINE socket))
                ; Print data on the output
                (FORMAT T "~&Output: ~A~%~%" input)
                (FORCE-OUTPUT T)
                (INCF i)
                (RETURN)
        )
        ; Close the connection
        (FORCE-OUTPUT socket)
		(CLOSE socket)
        (FORMAT T "Connection closed~%")
        (FORCE-OUTPUT T)
    )
)

(DEFUN recognize ()
	(loop 
		(socketClient SERVER_IP SERVER_PORT "recognize")
	(sleep 5)))

(setf k 0)
(recognize)
