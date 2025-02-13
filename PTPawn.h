#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PTPawn.generated.h"

class UBoxComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;

struct FInputActionValue; //??

UCLASS()
class PT_ACTOR_API APTPawn : public APawn
{
    GENERATED_BODY()

public:
    // 생성자
    APTPawn();

protected:

	virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void BeginPlay() override;

    // 컴포넌트
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PTPawn|Components")
    UBoxComponent* BoxComp;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PTPawn|Components")
    USkeletalMeshComponent* SkeletalMeshComp;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PTPawn|Components")
    USpringArmComponent* SpringArmComp;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PTPawn|Components")
    UCameraComponent* CameraComp;

   
    // 이동 및 회전 함수
    UFUNCTION()
    void Move(const FInputActionValue& Value);
    UFUNCTION()
    void Look(const FInputActionValue& Value);
   

	// 이동 속도
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 500.0f;

    
/*
    // 회전 속도
    UPROPERTY(EditAnywhere, Category = "Camera")
    float LookSensitivity = 2.0f;

    // 현재 회전 값
    float TargetYaw;
    float TargetPitch;
 */
};