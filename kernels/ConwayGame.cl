int get(int coord, int axis) {
    return (axis + (coord % axis)) % axis;
}

bool computeRules(int neighbours, bool stateCell) {
    if(stateCell){
        return neighbours == 3 || neighbours == 2;
    }
    return neighbours == 3;
}

__kernel void ConwayGame(__global bool* grid, __global bool* mask, int x, int y){
    int i = get_global_id(0), j = get_global_id(1);

    int neighbours = grid[(j - 1)%y + i * y] + grid[(j + 1)%y + i*y] +
                     grid[j + get((i - 1), x) * y] +  grid[j + (i + 1)%x * y] +
                     grid[get((j - 1), y) +  get((i - 1), x) * y] +
                     grid[(j + 1)%y + get((i - 1), x) * y] +
                     grid[get((j - 1), y) + (i + 1) % x * y] +
                     grid[(j + 1)%y + (i + 1)%x * y];

    mask[j + i * y] = computeRules(neighbours,  grid[j + i * y]);
}