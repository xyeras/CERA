#ifndef POSTS_H
#define POSTS_H

typedef struct
{
    float x;
    float y;
    float radius;
}circles;

class Posts
{
    public:
        Posts();
        virtual ~Posts();

        circles lights[2];

        float getRadius(int);
        float getX(int);
        float getY(int);

    protected:

    private:
};

#endif // POSTS_H
