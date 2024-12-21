


#pragma once

class ranged_char
{
public:
    ranged_char(){}
    ranged_char(unsigned char min_val, unsigned char max_val)
        : min_val_(min_val), max_val_(max_val)
    {
    }

    void set_val(unsigned char val) {
        valid_ = 
            val >= min_val_ and
            val <= max_val_;

        if (valid_) {
            val_ = val;
        }
    }

    unsigned char get_val() const {
        return val_;
    }
    
    bool is_valid() const {
        return valid_;
    }

private:
    bool valid_{false};
    unsigned char min_val_{0};
    unsigned char max_val_{0};
    unsigned char val_{0};
};

