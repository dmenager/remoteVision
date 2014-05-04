#include "ubyteextractor.h"

using namespace std;


UbyteExtractor::UbyteExtractor()
{
}

UbyteExtractor::~UbyteExtractor()
{
}

void UbyteExtractor::convert()
{

    fstream fin("/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/train-images.idx3-ubyte");
    fstream fin2("/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/train-labels.idx1-ubyte");
    fstream fin3("/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/t10k-images.idx3-ubyte");
    fstream fin4("/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/t10k-labels.idx1-ubyte");
    ofstream fout("dataSet.csv",  ios_base::app | ios_base::ate);
    ofstream log("log.txt");

    build(fin, fin2, fout, log);
    build(fin3, fin4, fout, log);


    fin.close();
    fin2.close();
    fin3.close();
    fin4.close();
    fout.close();
    log.close();
}

void UbyteExtractor::build(fstream& fin, fstream& fin2, ofstream& fout, ofstream& log)
{
    if (fin.is_open())
    {
        int magic_number=0, magic_number_l = 0;
        int number_of_images=0, number_of_items = 0;
        int n_rows=0;
        int n_cols=0;
        if ( ! fin.read((char*)&magic_number,sizeof(magic_number)))
            log << "Failed to read from fin\n";
        magic_number= ntohl(magic_number);

        if(!fin2.read((char*)&magic_number_l, sizeof(magic_number_l)))
        {
            log << "Failed to read from fin2\n";
        }
        magic_number_l = ntohl(magic_number_l);
        if ( ! fin.read((char*)&number_of_images,sizeof(number_of_images)))
            log << "Failed to read from fin\n";
        number_of_images= ntohl(number_of_images);

        if ( ! fin2.read((char*)&number_of_items,sizeof(number_of_items)))
        {
            log << "Failed to read from fin\n";
        }
        number_of_items = ntohl(number_of_items);

        if ( ! fin.read((char*)&n_rows,sizeof(n_rows)))
            log << "Failed to read from fin\n";
        n_rows= ntohl(n_rows);
        if ( ! fin.read((char*)&n_cols,sizeof(n_cols)))
            log << "Failed to read from fin\n";
        n_cols= ntohl(n_cols);

        log << "Mgc==" << magic_number << "; NImg==" << number_of_images << "; "
            "NRow==" << n_rows << "; NCol==" << n_cols << endl;
        for(int i=0;i<number_of_images;++i)
        {
            //log << '[' << endl;
            for(int r=0;r<n_rows;++r)
            {
                //log << '\t' << '[' ;
                for(int c=0;c<n_cols;++c)
                {
                    unsigned char temp=0;
                    if ( ! fin.read((char*)&temp,sizeof(temp)))
                        log << "Failed to read from fin\n";
                    fout << unsigned(temp) << ", " ;
                }
                //log << ']' << endl;
                //fout << endl;
            }

            //log << ']' << endl;

            unsigned char ans = 0;

            if(!fin2.read((char*)&ans, sizeof(ans)))
            {
                log << "Failed to read from fin2.\n";
            }

            string answer;
            switch(unsigned(ans))
            {
                case 0:
                {
                    answer = "0, 0, 0, 0, 0, 0, 0, 0, 0, 0";
                    break;
                }
                case 1:
                {
                    answer = "0, 0, 0, 0, 0, 0, 0, 0, 1, 0";
                    break;
                }
                case 2:
                {
                    answer = "0, 0, 0, 0, 0, 0, 0, 1, 0, 0";
                    break;
                }
                case 3:
                {
                    answer = "0, 0, 0, 0, 0, 0, 1, 0, 0, 0";
                    break;
                }
                case 4:
                {
                    answer = "0, 0, 0, 0, 0, 1, 0, 0, 0, 0";
                    break;
                }
                case 5:
                {
                    answer = "0, 0, 0, 0, 1, 0, 0, 0, 0, 0";
                    break;
                }
                case 6:
                {
                    answer = "0, 0, 0, 1, 0, 0, 0, 0, 0, 0";
                    break;
                }
                case 7:
                {
                    answer = "0, 0, 1, 0, 0, 0, 0, 0, 0, 0";
                    break;
                }
                case 8:
                {
                    answer = "0, 1, 0, 0, 0, 0, 0, 0, 0, 0";
                    break;
                }
                case 9:
                {
                    answer = "1, 0, 0, 0, 0, 0, 0, 0, 0, 0";
                    break;
                }

            }

            fout << answer  << endl;
        }
    }

}
