package fileopen

import (
	"fmt"
	"io"
	"os"
)

func WriteToFile(fileName string) {
	// file open
	file, err := os.Create(fileName)
	if err != nil {
		panic(err)
	}
	defer func() {
		if err := file.Close(); err != nil {
			panic(err)
		}
	}()

	n, err := file.WriteString("hello world\n")
	if err != nil {
		panic(err)
	}
	fmt.Printf("wrote %d bytes\n", n)
}

func ReadFromFile(fileName string) {
	// file open
	file, err := os.Open(fileName)
	if err != nil {
		panic(err)
	}
	defer func() {
		if err := file.Close(); err != nil {
			panic(err)
		}
	}()
	buf := make([]byte, 1024)
	for {
		// read chunk
		n, err := file.Read(buf)
		if err != nil && err != io.EOF {
			panic(err)
		}
		if n == 0 {
			break
		}

		fmt.Printf("%d bytes: %s\n", n, string(buf))
	}

}
