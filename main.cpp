#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
using namespace std;

const int populationSize =40, numOfIterations = 100;
const double Pc = 0.5, Pm = 0.05;
int cnt=0;

class Chromosome {
private:
    ll degree=0;
    long double fitness{};
    long double totalError{};
    vector<pair<long double,long double>> allItems;
    int itemNum{};
public:
    vector<long double> genes;
    Chromosome() {
        itemNum=++cnt;
    }
    virtual ~Chromosome() = default;
    void setItems(ll d) {
        this->degree=d;
        genes.resize(this->degree);
    }
    void calcFitness(const vector<pair<long double,long double>>& items){
        allItems=items;
        long double sum,finalError=0.0;
        for(const auto & item : items){
            sum=genes[0];
            for(int j=1;j<genes.size();j++)
                sum+=(genes[j]*pow(item.first,j));
            sum-=item.second;
            sum*=sum;
            finalError+=sum;
        }
        this->totalError=(finalError/items.size());
        this->fitness=(1/this->totalError);
    }
    [[nodiscard]] long double getFitness() const {
        return fitness;
    }
    [[nodiscard]] long double getTotalError() const {
        return totalError;
    }
    [[nodiscard]] vector<pair<long double, long double>> getAllItems() const {
        return allItems;
    }
};

//sort by values by inverse
bool compareVal(const Chromosome& c1,const Chromosome& c2){
    return c1.getFitness()>c2.getFitness();
}

class GA{
private:
    vector<Chromosome>* solutions;
    vector<Chromosome> offsprings;
    int numOfOffsprings; // for divide offsprings and population

    //utility functions
    Chromosome tournament(){
        auto & sol=*solutions;
        Chromosome bestChromosome,chromosome;
        std::random_device rd; // random number
        std::mt19937 gen(rd()); // the generator
        std::uniform_int_distribution<> distribution(0,(int) sol.size()-3); // define the range
        bestChromosome=sol[distribution(gen)];

        for(int i=1;i<this->numOfOffsprings;i++){
            chromosome=sol[distribution(gen)];
            chromosome.calcFitness(sol[0].getAllItems());bestChromosome.calcFitness(sol[0].getAllItems());
            if(chromosome.getFitness()<bestChromosome.getFitness()) bestChromosome=chromosome;
        }
        return bestChromosome;
    }
    void elitism(){
        auto & sol=*solutions;
        sort(sol.begin(),sol.end(), compareVal); // min error in the last
        for(int i=0;i<offsprings.size();i++)
            sol[i]=offsprings[i];
    }
public:
    explicit GA(vector<Chromosome>& solutions) {
        this->solutions=&solutions;
        this->numOfOffsprings=(int)this->solutions->size()/2;
        offsprings.resize(this->numOfOffsprings);
    }
    void initializePopulation(){
        for(auto & solution : *solutions){
            for(auto && gene : solution.genes){
                gene=((float(rand())/float(RAND_MAX))*(10+10))-10;
            }
        }
    }
    void selection(){
        auto & sol=*solutions;
        sort(sol.begin(),sol.end(), compareVal); // min error in the last
        for(int i=0;i<numOfOffsprings;i++)
            offsprings[i]=this->tournament();
    }
    void crossOver(){
        for(int i=0;i<offsprings.size();i++){
            for(int j=i+1;j<offsprings.size();j++){
                double randNum=((double) rand() / (RAND_MAX));
                if(randNum<Pc){
                    int randNumIdx=rand()%(offsprings[i].genes.size()-2);
                    for(int k=randNumIdx;k<offsprings[i].genes.size();k++)
                        swap(offsprings[i].genes[k],offsprings[j].genes[k]);
                }
            }
        }
    }
    void mutation(ll t){
        for(auto & offspring : offsprings){
            long double maxVal=-1e9,minVal=1e9;
            for(auto && gene : offspring.genes)
                if(gene>maxVal) maxVal=gene;

            for(auto && gene : offspring.genes)
                if(gene<minVal) minVal=gene;

            for(auto && gene : offspring.genes){
                double randNum=((double)rand()/(RAND_MAX));
                if(randNum<Pm) {
                    long double dLower=gene-minVal,dUpper=maxVal-gene,y=0,newVal;
                    double randNum1=((double) rand() / (RAND_MAX));
                    y=randNum1<=0.5?dLower:dUpper;
                    newVal=y*(1-pow(randNum1, pow(1-t/numOfIterations,2)));
                    gene=(y==dLower)?gene-newVal:gene+newVal;
                }
            }
        }
    }
    void replacement(){
        elitism();
    }
};

int main() {
    srand(time(nullptr));
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    ll numOftestCases,numOfItems,degree,iterationsSize,testNum=1;cin>>numOftestCases;
    while(numOftestCases--){
        iterationsSize=numOfIterations;
        cin>>numOfItems>>degree;
        vector<pair<long double,long double>> items(numOfItems);
        for(auto i=0;i<numOfItems;i++) cin>>items[i].first>>items[i].second;
        vector<Chromosome> solutions(populationSize);
        for (int i = 0; i < populationSize; i++)
            solutions[i].setItems(degree+1);
        GA geneticAlgorithm(solutions);

        //First Step (Initialize Pool Of Solutions)
        geneticAlgorithm.initializePopulation();

        while(iterationsSize--){
            //Second Step (Individual Evaluation)
            for (int i = 0; i < populationSize; i++) solutions[i].calcFitness(items);

            //Third Step (Selection)
            geneticAlgorithm.selection();

            //Fourth Step (Crossover)
            geneticAlgorithm.crossOver();

            //Fifth Step (Mutation)
            geneticAlgorithm.mutation(testNum);

            //Sixth Step (Reproduction)
            geneticAlgorithm.replacement();
        }
        sort(solutions.begin(),solutions.end(), compareVal);

        //printing
        cout<<"Testcase "<<testNum++<<":\nThe Coefficients: [ ";
        for(auto && gene : solutions[solutions.size()-1].genes){
            cout<<std::fixed<<std::setprecision(2);
            gene!=solutions[solutions.size()-1].genes[solutions[solutions.size()-1].genes.size()-1]?
            cout<<gene<<" , ":
            cout<<gene<<" ";
        }
        cout<<"]"<<endl<<"Mean Square Error: "<<std::fixed<<std::setprecision(20)
        <<solutions[solutions.size()-1].getFitness()<<endl<<endl;
    }
    return 0;
}
