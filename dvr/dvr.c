#include<stdio.h>

struct router {
    int cost[20];
    int from[20];
} routingTable[10];

int main() {
    int costmat[20][20];
    int routes;

    printf("Enter the number of routers: ");
    scanf("%d", &routes);

    printf("Enter the cost matrix:\n");
    for (int i = 0; i < routes; i++) {
        costmat[i][i] = 0;
        for (int j = 0; j < routes; j++) {
            scanf("%d", &costmat[i][j]);
            routingTable[i].cost[j] = costmat[i][j];
            routingTable[i].from[j] = j;
        }
    }

    int shortPathFlag;

    do {
        shortPathFlag = 0;

        for (int i = 0; i < routes; i++) {
            for (int j = 0; j < routes; j++) {
                for (int k = 0; k < routes; k++) {
                    if (routingTable[i].cost[j] > costmat[i][k] + routingTable[k].cost[j]) {
                        routingTable[i].cost[j] = costmat[i][k] + routingTable[k].cost[j];
                        routingTable[i].from[j] = k;
                        shortPathFlag = 1;
                    }
                }
            }
        }
    } while (shortPathFlag != 0);

    for (int i = 0; i < routes; i++) {
        printf("For router %d:\n", i + 1);
        for (int j = 0; j < routes; j++) {
            printf("Cost of %d from %d is %d\n", j + 1, routingTable[i].from[j] + 1, routingTable[i].cost[j]);
        }
        printf("\n");
    }

    return 0;
}
