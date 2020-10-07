#ifndef LAB1_RNA_H
#define LAB1_RNA_H

#include <unordered_map>
#define PAIRS_IN_SIZE_T (sizeof(size_t) * 4)

using namespace std;

enum Nucleotide { A, G, C, T };

class RNA {
private:
    Nucleotide _nucl = A;
    size_t _size = 0;
    size_t _capacity = 0;
    size_t *_nucleotides = nullptr;

    void update_capacity();
    size_t fill_nucleotides(Nucleotide nucleotide);

    void add_nucleotide(Nucleotide);
    Nucleotide get_nucleotide(size_t index) const;
    void set_nucleotide(Nucleotide nucleotide, size_t index);

public:
    class nucl_ref {
    private:
        RNA *_rna;
        size_t _idx = 0;
    public:
        nucl_ref(RNA &rna, size_t idx);
        operator Nucleotide() const;
        nucl_ref& operator=(Nucleotide nucleotide);
    };

    class const_nucl_ref {
    private:
        const RNA *_rna;
        size_t _idx = 0;
    public:
        const_nucl_ref(const RNA &rna, size_t idx);
        operator Nucleotide() const;
    };

    //constructors and destructors//
    RNA(Nucleotide nucleotide, size_t capacity);
    RNA(const RNA &rna);
    virtual ~RNA();

    //general
    size_t length();
    size_t capacity();

    void trim(size_t from);
    std::pair<RNA, RNA> split(size_t index);

    bool is_complementary(const RNA& rna);

    size_t cardinality(Nucleotide value);
    std::unordered_map<Nucleotide, int> cardinality();

    //operators
    RNA& operator=(const RNA& rna);
    RNA& operator+=(Nucleotide nucleotide);
    friend RNA operator+(const RNA& rna1, RNA const& rna2);
    friend bool operator==(const RNA& rna1, const RNA& rna2);
    friend bool operator!=(const RNA& rna1, const RNA& rna2);
    RNA operator!();
    nucl_ref operator[](size_t index);
    const_nucl_ref operator[](size_t index) const;
    friend std::ostream& operator<<(std::ostream& os, const RNA& rna);
};

#endif
