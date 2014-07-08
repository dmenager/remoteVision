#include "ubyteextractor.h"

using namespace std;
using namespace cv;


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
    ofstream fout("answers.csv",  ios_base::app | ios_base::ate);
    ofstream pfout("dataSet.csv", ios_base::app | ios_base::ate);
    ofstream log("log.txt");

    vector <vector<pixel> > master;
    vector <vector<pixel> > training;
    vector <vector<pixel> > verify;

    training = build(fin, fin2, fout, log);
    verify = build(fin3, fin4, fout, log);


    //DEBUG
/*
    for(int i = 0; i < verify.size(); i++)
    {
        for(int j = 0; j < verify.at(i).size(); j++)
        {
            cout << "verify " << i <<".x: " << verify.at(i).at(j).x << "\t" << "verify " << i << ".y: " << verify.at(i).at(j).y << "\n";
        }
    }
*/


    master = training;

    fin.close();
    fin2.close();
    fin3.close();
    fin4.close();
    fout.close();
    log.close();


    if(training.at(0).at(0).x != -1  && verify.at(0).at(0).x != -1)
    {

        for(int i = 0; i < verify.size(); i++) //10000 = number of validation set images
        {
            master.push_back(verify[i]);
        }

        //make training dataset
        //delete [] verify;

        cout << "Applying radon transform\n";
        radonTransformer rT;
        fstream reader("answers.csv");

        float* preProcessed;
        for(int i = 0; i < master.size(); i++)
        {
            rT.transform(master.at(i));
            preProcessed = rT.getTotals();

            //cast 1d array to 2d array
            float (*pp)[11] = (float (*)[11]) preProcessed;


            //vectorize
            for(int j = 0; j < 8; j++)
            {
                for(int k = 0; k < 11; k++)
                {
                    pfout << pp[j][k]<< ", ";
                }
            }
            string ans = "";
            //attatch answer
            getline(reader, ans);
            pfout << ans << endl;
        }

        pfout.close();
        reader.close();
    }
    else if(training.at(0).at(0).x == -1  && verify.at(0).at(0).x == -1)
    {
        cout << "Error: Both sets are null\n";
    }
    else if(training.at(0).at(0).x == -1  && verify.at(0).at(0).x != -1)
    {
        cout << "Error: Training is null\n";
    }
    else if(training.at(0).at(0).x != -1  && verify.at(0).at(0).x == -1)
    {
        cout << "Error: Verify is null\n";
    }

}

vector <vector <pixel> > UbyteExtractor::build(fstream& fin, fstream& fin2, ofstream& fout, ofstream& log)
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

        //make a list for all the radoned images
        vector <vector<pixel> > RPics(number_of_images);
        for(int i=0;i<number_of_images;++i)
        {
            //cv::Mat img = cv::Mat(cv::Size(n_rows, n_cols), CV_8UC1);
            //img.zeros(n_rows, n_cols, CV_8UC1);

            vector<pixel> radon;
            //log << '[' << endl;
            for(int r=0;r<n_rows;++r)
            {                
                //log << '\t' << '[' ;
                for(int c=0;c<n_cols;++c)
                {
                    unsigned char temp=0;
                    if ( ! fin.read((char*)&temp,sizeof(temp)))
                    {
                        log << "Failed to read from fin\n";
                    }
                    //img.at<uchar>(r,c) = unsigned(temp);
                    if(unsigned(temp) >= 1) //175
                    {
                        //we don't care what the pixel value is. This is in essence building a binary image
                        pixel idx;
                        idx.x = r;
                        idx.y = c;
                        radon.push_back(idx);
                        //DEBUG
                        //cout << "set " << i << ".x :" << idx.x << "\tset " << i <<".y :" <<idx.y << "\n";
                    }
                    //fout << unsigned(temp) << ", " ;
                }

                //log << ']' << endl;
                //fout << endl;               
            }
            //imshow("db", img);
            //waitKey(0);
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
                    answer = "0";
                    break;
                }
                case 1:
                {
                    answer = "1";
                    break;
                }
                case 2:
                {
                    answer = "2";
                    break;
                }
                case 3:
                {
                    answer = "3";
                    break;
                }
                case 4:
                {
                    answer = "4";
                    break;
                }
                case 5:
                {
                    answer = "5";
                    break;
                }
                case 6:
                {
                    answer = "6";
                    break;
                }
                case 7:
                {
                    answer = "7";
                    break;
                }
                case 8:
                {
                    answer = "8";
                    break;
                }
                case 9:
                {
                    answer = "9";
                    break;
                }

            }
            RPics.at(i) = radon;           

            //DEBUG
            /*for(int z = 0; z < radon.size(); z++)
            {
                cout << "("<< radon.at(z).x << ", " << radon.at(z).y << ") ";
            }*/

            fout << answer  << endl;
        }
        //DEBUG
        /*for(int i = 0; i < number_of_images; i++)
        {
            for(int j = 0; j < RPics.at(i).size(); j++)
            {
                cout << "RPICS " << i << ".x :" << RPics.at(i).at(j).x << "\tRPICS " << i << ".y :" << RPics.at(i).at(j).y << "\n";
            }
        }*/
        return RPics;
    }
    pixel invalid;
    invalid.x = -1;
    invalid.y = -1;
    vector <vector <pixel> > inv(1, vector<pixel>(1, invalid));
    return inv;
}
